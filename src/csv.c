#include "../include/csv.h"

int count_lines(FILE *fd) {
    char *line = NULL;
    size_t len = 0, read;
    int n = 0;

    while ((read = getline(&line, &len, fd)) != (size_t)-1)
        n++;
    
    rewind(fd);
    return n - 1;
}

void export_csv(FILE *csv, network networks[], int n) {
    char *buffer = (char *)malloc(16 * sizeof(char));
    fprintf(csv, "IP, CIDR, Broadcast, Start, End, Free from, to\n");

    for (int i = 0; i < n; i++) {
        fprintf(csv, "%s, ", int2ip(buffer, networks[i].start - 1));
        fprintf(csv, "%d, ", networks[i].cidr);
        fprintf(csv, "%s, ", int2ip(buffer, networks[i].broadcast));

        if (is_free(networks[i])) {
            fprintf(csv, " //, //, %s,", int2ip(buffer, networks[i].start));
        } else {
            fprintf(csv, " %s, ", int2ip(buffer, networks[i].start));
            fprintf(csv, " %s, ", int2ip(buffer, networks[i].end));
            fprintf(csv, "  %s, ", int2ip(buffer, networks[i].end + 1));
        }
        
        fprintf(csv, "%s\n", int2ip(buffer, networks[i].broadcast - 1));
    }

    free(buffer);
}

char *getfield(char *line, int num) {
    char *tok;

    for (tok = strtok(line, ", "); tok && *tok; tok = strtok(NULL, ", "))
        if (!--num)
            return tok;

    return NULL;
}

void handle_no_value(char *tok, char *copy, char *line, int target_column) {
    if (!strcmp(tok, "//") && target_column == START) {
        strcpy(copy, line);
        tok = getfield(copy, NETIP);
    }
}

int get_csv_element(char *line, int target_column) {
    char *copy = (char *)malloc((strlen(line) + 1) * sizeof(char));
    strcpy(copy, line);

    char *tok = getfield(copy, target_column);
    handle_no_value(tok, copy, line, target_column);

    int value = ip2int(tok);
    free(copy);
    return value;
}

int parse_csv(FILE *csv, network **networks) {
    char *line = NULL;
    size_t len = 0;
    int n_networks = count_lines(csv);
    *networks = (network *)malloc(n_networks * sizeof(network));

    getline(&line, &len, csv);
    for (int i = 0; i < n_networks; i++) {
        getline(&line, &len, csv);

        (*networks)[i] = (network){
            
            get_csv_element(line, START),
            get_csv_element(line, END),

            get_csv_element(line, BROADCAST),
            get_csv_element(line, CSV)
        };
    }

    free(line);
    return n_networks;
}