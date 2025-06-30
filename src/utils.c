#include "../include/utils.h"

int all_1(int num, int start, int end) {  
    num >>= 32 - end;

    int i = 0;
    while (num & 1 && i < end - start) {
        num >>= 1;
        i++;
    }

    return i == end - start;
}

network build_network(int ip, int n_devices, int cidr) {
    network net = {ip + 1, ip + n_devices, get_broadcast(ip, cidr), cidr};
    return net;
}

int find_power_bigger_than(int num) {
    for (int i = 0; i < 32; i++) 
        if (pow(2, i) > num)
            return i;
    
    return 0;
}

int get_broadcast(int ip, int cidr) {
    int b = 0;

    for (int i = cidr; i < 32; i++)
        b = b * 2 + 1;
    
    return ip | b;
}

int get_hostid(int ip, int cidr) {
    return ip & get_subnet_mask(cidr);
}

int get_subnet_mask(int cidr) {
    int subnet_mask = 0;

    for (int i = 0; i < 32 - cidr; i++)
        subnet_mask = subnet_mask * 2 + 1;
    
    return subnet_mask;
}

char *int2ip(char ip[], unsigned int bits) {
    unsigned int octets[4] = {0, 0, 0, 0};
    
    for (int i = 0; i < 4; i++) {
        octets[i] = bits & 0xFF;
        bits >>= 8;
    }

    int last = sprintf(ip, "%d.%d.%d.%d", octets[3], octets[2], octets[1], octets[0]);
    ip[last] = '\0';

    return ip;
}

unsigned int ip2int(char ip[]) {
    int i = -1;
    unsigned int partial = 0, sum = 0;

    while (ip[++i] != '\0')
        if (ip[i] != '.') {
            partial = partial * 10 + (ip[i] - '0');
        } else {
            sum = (sum << 8) + partial;
            partial = 0;
        }
    
    return (sum << 8) + partial;
}

int not_valid(network net) {
    return net.broadcast <= net.end;
}

network *realloc_network(network *ptr, int size) {
    return (network *)realloc(ptr, size * sizeof(network));
}

void sort(int nums[], int n) {
    int temp;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if (nums[j] < nums[j + 1]) {
                temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
}
