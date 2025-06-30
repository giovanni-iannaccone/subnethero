#include "../include/vlsm.h"

int vlsm(network **networks, int devices[], int ip, int cidr, int n_networks) {
    int i = 0, new_cidr = cidr;
    int n_devices;

    sort(devices, n_networks);
    *networks = (network *)malloc(n_networks * sizeof(network));
    
    while(!all_1(ip, cidr, new_cidr)) {
        
        if (i > n_networks) {
            *networks = (network *)realloc(*networks, i * sizeof(network));
            new_cidr = 32 - new_cidr;
            n_devices = 1;

        } else {
            new_cidr = 32 - new_cidr - find_power_bigger_than(devices[i]);
            n_devices = devices[i];
        }

        (*networks)[i] = build_network(ip + 1, ip + n_devices, get_broadcast(ip, new_cidr), new_cidr);

        ip += 1 * pow(2, 32 - new_cidr);
        i++;
    }

    *networks = (network *)realloc(*networks, i * sizeof(network));
    (*networks)[i] = build_network(ip + 1, ip + n_devices, get_broadcast(ip, new_cidr), new_cidr);

    return i;
}