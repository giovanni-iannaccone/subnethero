#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/csv.h"
#include "../include/data.h"
#include "../include/utils.h"

#include "../include/lookup.h"

#include "../include/flat.h"
#include "../include/flsm.h"
#include "../include/vlsm.h"

#define VERSION "1.0"

typedef struct {
    approaches approach;

    int cidr;
    int ip;

    int n_networks;
    int *devices;

    char *input;
    char *output;

    int iplookup;
} arguments;

static inline int compare_flag(const char value[], const char flag[], const char extended[]) {
    return !strcmp(value, flag) || !strcmp(value, extended);
}

int *get_devices(char *devices[], int n) {
    int *d = (int *)malloc(n *  sizeof(int));

    for (int i = 0; i < n; i++)
        d[i] = atoi(devices[i]);

    return d;
}

void help(const char program_name[]) {
    printf("%s v%s\n Usage:\n", program_name, VERSION);

    printf("%s [-t | -f | -v] -c cidr -i ip -d n {n devices for each network}\n\n", program_name);

    printf("-t | --flat\t\tuse the flat approach\n");
    printf("-f | --flsm\t\tuse the flsm approach\n");
    printf("-v | --vlsm\t\tuse the vlsm approach\n\n");

    printf("-i | --ip\t\tspecify the IP of the base network\n");
    printf("-c | --cidr\t\tthe CIDR of the original network\n");
    printf("-s | --subs\t\tnumber of subnetworks (followed by n devices for each network)\n\n");

    printf("Optional:\n");
    printf("-p | --input\t\tread network configuration from a csv file\n");
    printf("-o | --output\t\tcopy the output into csv file\n");
    printf("-l | --lookup\t\tfind which subnet owns an ip\n\n");

    printf("Example: %s -v -c 24 -i 192.168.1.0 -s 3 64 5 15\n\n", program_name);
}

arguments parse_arguments(int argc, char *argv[]) {
    arguments args = {flat_approach, 24, 0, 0, NULL, NULL, NULL, 0};

    for (int i = 0; i < argc; i++)
        if (compare_flag(argv[i], "-t", "--flat"))
            args.approach = flat_approach;
        
        else if (compare_flag(argv[i], "-f", "--flsm"))
            args.approach = flsm_approach;
        
        else if (compare_flag(argv[i], "-v", "--vlsm"))
            args.approach = vlsm_approach;
        
        else if (compare_flag(argv[i], "-c", "--cidr"))
            args.cidr = atoi(argv[i + 1]);
        
        else if (compare_flag(argv[i], "-i", "--ip"))
            args.ip = ip2int(argv[i + 1]);

        else if (compare_flag(argv[i], "-s", "--subs")) {
            args.n_networks = atoi(argv[i + 1]);
            args.devices = get_devices(argv + i + 2, atoi(argv[i + 1]));
        
        } else if (compare_flag(argv[i], "-p", "--input"))
            args.input = argv[i + 1];
        
        else if (compare_flag(argv[i], "-o", "--output"))
            args.output = argv[i + 1];
        
        else if (compare_flag(argv[i], "-l", "--lookup"))
            args.iplookup = ip2int(argv[i + 1]);
    
    return args;
}

void print_lookup_result(network networks[], int n, int ip) {
    char buffer[16];
    unsigned int subnet_ip_belongs = lookup(networks, n, ip);

    if (subnet_ip_belongs == 0) {
        printf("%s is not in any network\n", int2ip(buffer, ip));
    } else {
        printf("%s is in subnet ", int2ip(buffer, ip));
        printf("%s\n", int2ip(buffer, subnet_ip_belongs));
    }
}

void print_net(network net) {
    char buffer[16];

    printf("| %s |", int2ip(buffer, net.start - 1));
    printf(" /%d  |", net.cidr);
    printf(" %s |", int2ip(buffer, net.broadcast));
    
    if (is_free(net)) {
        printf(" // | // | %s |", int2ip(buffer, net.start));
    } else {
        printf(" %s |", int2ip(buffer, net.start));
        printf(" %s |", int2ip(buffer, net.end));
        printf("  %s |", int2ip(buffer, net.end + 1));
    }

    printf(" %s |\n", int2ip(buffer, net.broadcast - 1));
}

void print_table(network networks[], int n) {
    printf("|     IP     | CIDR |   Broadcast   |    Start    |     End      |  Free from   |       to      |\n");
    printf("-------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
        print_net(networks[i]);
}

int run(const arguments args, network **networks) {
    if (args.input != NULL) {
        FILE *fd = fopen(args.input, "r");
        int n_networks = parse_csv(fd, networks);
        fclose(fd);

        return n_networks;
    }

    switch (args.approach) {
        case flat_approach:
            return flat(networks, args.devices, args.ip, args.cidr, args.n_networks);

        case flsm_approach:
            return flsm(networks, args.devices, args.ip, args.cidr, args.n_networks);

        default:
            return vlsm(networks, args.devices, args.ip, args.cidr, args.n_networks);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    arguments args = parse_arguments(argc, argv);
    network *networks;

    int n_networks = run(args, &networks);
    if (n_networks == 0) {
        printf("This approach can't be used on this network\n");
        exit(EXIT_FAILURE);
    
    } else if (args.iplookup) {
        print_lookup_result(networks, n_networks, args.iplookup);

    } else if (args.output != NULL) {
        FILE *fd = fopen(args.output, "w");
        export_csv(fd, networks, n_networks);
        fclose(fd);

    } else if (args.input == NULL) {
        print_table(networks, n_networks);
    }

    free(networks);
    free(args.devices);

    printf("\n\n");
    return 0;
}