#include "../include/flsm.h"

int flsm(network networks[], int devices[], int ip, int cidr, int n_networks) {
    int partial_cidr_len = find_power_bigger_than(n_networks);
    if (partial_cidr_len == 0)
        return 0;

    int new_cidr = cidr + partial_cidr_len;
    int partial_cidr = 0;
    int max = pow(2, partial_cidr_len);

    for (int i = 0; i < max; i++) {

        int n_devices = i < n_networks
            ? devices[i]
            : 0;

        networks[i] = build_network(
            ip + (partial_cidr << (32 - cidr + partial_cidr_len)),
            ip + (partial_cidr << (32 - cidr + partial_cidr_len)) + n_devices,
            get_broadcast(ip,  cidr),
            new_cidr
        );
                
        partial_cidr++;
    }

    return max;
}