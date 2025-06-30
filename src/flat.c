#include "../include/flat.h"

int flat(network **networks, int devices[], int ip, int cidr, int n_networks) {
    int sum = 0;

    for (int i = 0; i < n_networks; i++)
        if (devices[i] < get_broadcast(ip, cidr) - ip)
            sum += devices[i];
        else 
            return 0;

    int broadcast = get_broadcast(ip, cidr);

    *networks = (network *)malloc(sizeof(network));
    (*networks)[0] = build_network(ip + 1, ip + sum, broadcast, cidr);
    
    return 1;
}