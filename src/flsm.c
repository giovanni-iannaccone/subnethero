#include "../include/flsm.h"

int get_cidr(int cidr, int n_occupied_networks) {
    return cidr + find_power_bigger_than(n_occupied_networks);
}

int get_next_subnet_ip(int ip, int cidr) {
    return ip + pow(2, 32 - cidr);
}

int flsm(network **networks, int devices[], int ip, int cidr, int n_occupied_networks) {
    int n_devices = 0;

    int new_cidr = get_cidr(cidr, n_occupied_networks);
    if (new_cidr < cidr)
        return 0;
    
    int n_total_networks = pow(2, new_cidr - cidr);
    *networks = (network *)malloc(n_total_networks * sizeof(network));

    for (int i = 0; i < n_total_networks; i++) {
        n_devices = i >= n_occupied_networks
            ? NO_DEVICES
            : devices[i];
        
        (*networks)[i] = build_network(ip, n_devices, new_cidr);
        if (not_valid((*networks)[i]))
            return 0;

        ip = get_next_subnet_ip(ip, new_cidr);
    }

    return n_total_networks;
}