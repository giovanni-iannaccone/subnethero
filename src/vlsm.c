#include "../include/vlsm.h"

int vlsm(network **networks, int devices[], int ip, int cidr, int n_networks) {
    int i = 0, new_cidr = cidr;
    int n_devices;

    sort(devices, n_networks);
    *networks = (network *)malloc(n_networks * sizeof(network));
    
    do {
        if (i >= n_networks) {
            *networks = realloc_network(*networks, i + 1);
            n_devices = NO_DEVICES;

        } else {
            new_cidr = 32 - find_power_bigger_than(devices[i] + 2);
            if (new_cidr < cidr)
                return 0;

            n_devices = devices[i];
        }

        (*networks)[i] = build_network(ip, n_devices, new_cidr);
        if (not_valid((*networks)[i]))
            return 0;
        
        ip = get_next_subnet_ip(ip, new_cidr);
        i++;

    } while(!all_1(ip, cidr, new_cidr));

    *networks = realloc_network(*networks, i + 1);
    (*networks)[i] = build_network(ip, NO_DEVICES, new_cidr);

    return i + 1;
}