#include "../include/flat.h"

int flat(network **networks, int devices[], int ip, int cidr, int n_networks) {
    int sum = 0;
    int broadcast = get_broadcast(ip, cidr);

    for (int i = 0; i < n_networks; i++)
        if (devices[i] < broadcast - sum - ip)
            sum += devices[i];
        else 
            return 0;


    *networks = (network *)malloc(sizeof(network));
    (*networks)[0] = build_network(ip, sum, cidr);
    
    return 1;
}