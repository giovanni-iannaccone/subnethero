#include "../include/flsm.h"

int flsm(network **networks, int devices[], int ip, int cidr, int n_networks) {

    int i = 0, new_cidr = cidr + find_power_bigger_than(n_networks);
    if (new_cidr < cidr)
        return 0;

    int n_devices = 0;
    
    *networks = (network *)malloc(pow(2, new_cidr - cidr) * sizeof(network));

    while (!all_1(ip, cidr, new_cidr)) {

        n_devices = i >= n_networks
            ? 1
            : devices[i];
        
        (*networks)[i] = build_network(ip, n_devices, new_cidr);
        if (not_valid((*networks)[i]))
            return 0;

        ip += pow(2, 32 - new_cidr);
        i++;
    }

    (*networks)[i] = build_network(ip, 1, new_cidr);

    return i + 1;
}