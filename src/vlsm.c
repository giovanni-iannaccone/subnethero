#include "../include/vlsm.h"

int vlsm(network **networks, int devices[], int ip, int cidr, int n_networks) {
    int i = 0, new_cidr = cidr;
    int n_devices;

    sort(devices, n_networks);
    *networks = (network *)malloc(n_networks * sizeof(network));
    
    do {
        if (i >= n_networks) {
            *networks = (network *)realloc(*networks, (i + 1) * sizeof(network));
            n_devices = 1;

        } else {
            new_cidr = 32 - find_power_bigger_than(devices[i] + 2);
            if (new_cidr < cidr)
                return 0;

            n_devices = devices[i];
        }

        (*networks)[i] = build_network(ip + 1, ip + n_devices, get_broadcast(ip, new_cidr), new_cidr);
        if ((*networks)[i].broadcast <= (*networks)[i].end)
            return 0;
        
        ip += 1 * pow(2, 32 - new_cidr);
        i++;

    } while(!all_1(ip, cidr, new_cidr));

    *networks = (network *)realloc(*networks, (i + 1) * sizeof(network));
    (*networks)[i] = build_network(ip + 1, ip + n_devices, get_broadcast(ip, new_cidr), new_cidr);

    return i;
}