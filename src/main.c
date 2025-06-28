#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/data.h"

#include "../include/flat.h"
#include "../include/flsm.h"
#include "../include/vlsm.h"

typedef struct {
    approaches approach;

    int cidr;
    int ip;

    int n_networks;
    int *devices;
} arguments;

int compare_flag(const char value[], const char flag[], const char extended[]) {
    return strcmp(value, flag) || strcmp(value, extended);
}

int *get_devices(char *devices[], int n) {
    int *d = (int *)malloc(n *  sizeof(int));

    for (int i = 0; i < n; i++)
        d[i] = atoi(devices[i]);

    return d;
}

void help(const char program_name[]) {
    printf("%s v1.0\n Usage:\n", program_name);

    printf("%s [-t | -f | -v] -c cidr -i ip -d n {n devices for each network}\n\n", program_name);

    printf("-t | --flat\t\tuse the flat approach\n");
    printf("-f | --flsm\t\tuse the flsm approach\n");
    printf("-v | --vlsm\t\tuse the vlsm approach\n\n");

    printf("-i | --ip\t\tspecify the IP of the base network\n");
    printf("-c | --cidr\t\tthe CIDR of the original network\n");
    printf("-d | --devs\t\tnumber of subnetworks (followed by n devices for each network)\n\n");

    printf("Example: %s -v -c 24 -i 192.168.1.0 -d 3 64 5 15\n\n", program_name);
}

arguments parse_arguments(int argc, char *argv[]) {
    arguments args = {flat_approach, 24, 0, 0, NULL};

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
            args.ip = convert_to_int(argv[i + 1]);
        
        else if (compare_flag(argv[i], "-d", "--devs")) {
            args.n_networks = atoi(argv[i + 1]);
            args.devices = get_devices(argv + i + 2, argc - i - 1);
        }
    
    return args;
}

void print_net(network net) {
    printf("%s /%d %s %s %s %s %s", net.start, net.cidr, net.broadcast, net.start, net.last - net.end, net.last);
}

void print_table(network networks[], int n) {
    printf("|    IP   | CIDR | Broadcast |   Start   |     End    | Free from |    to    |\n");

    for (int i = 0; i < n; i++)
        print_net(networks[i]);
}

int run(const arguments args, network networks[]) {
    if (args.approach == flat_approach) 
        return flat(networks, args.devices, args.ip, args.cidr, args.n_networks);

    else if (args.approach == flsm_approach)
        return flsm(networks, args.devices, args.ip, args.cidr, args.n_networks);

    else
        return vlsm(networks, args.devices, args.ip, args.cidr, args.n_networks);    
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        help(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    arguments args = parse_arguments(argc, argv);
    network *networks = (network*)malloc(args.n_networks * sizeof(network));

    int len = run(args, networks);
    if (len == 0)
        printf("This approach can't be used on this network");
    else 
        print_table(networks, args.n_networks);
    
    printf("\n\n");
    return 0;
}