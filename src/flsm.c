#include "../include/flsm.h"

int flsm(network **networks, int devices[], int ip, int cidr, int n_networks) {

    int i = 0, new_cidr = cidr + find_power_bigger_than(n_networks);
    if (new_cidr < cidr)
        return 0;

    int n_devices = 0;

    *networks = (network *)malloc(n_networks * sizeof(network));

    while (!all_1(ip, cidr, new_cidr)) {

        if (i >= n_networks) {
            *networks = (network *)realloc(*networks, (i + 1) * sizeof(network));
            n_devices = 1;
            
        } else {
            n_devices = devices[i];
        }
        
        (*networks)[i] = build_network(ip + 1, ip + n_devices, get_broadcast(ip, new_cidr), new_cidr);
        if ((*networks)[i].broadcast <= (*networks)[i].end)
            return 0;

        ip += pow(2, 32 - new_cidr);
        i++;
    }

    *networks = (network *)realloc(*networks, (i + 1) * sizeof(network));
    (*networks)[i] = build_network(ip + 1, ip + 1, get_broadcast(ip, new_cidr), new_cidr);

    return i;
}