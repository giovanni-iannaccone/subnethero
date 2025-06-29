#include "../include/vlsm.h"

int vlsm(network networks[], int devices[], int ip, int cidr, int n_networks) {
    int i = 0, new_cidr = cidr;
    sort(devices, n_networks);
    
    while(!all_1(ip, cidr, new_cidr)) {
        new_cidr = 32 - new_cidr - find_power_bigger_than(devices[i]);

        networks[i] = build_network(
            ip + 1,
            ip + devices[i],
            get_broadcast(ip, new_cidr),
            new_cidr
        );

        ip += 1 * pow(2, 32 - new_cidr);
    }

    return i;
}