#include "../include/utils.h"

int all_1(int num, int start, int end) {  
    int i = 32;
    for (; i > end; i--)
        num >>= 1;
    
    i = 0;
    while (num & 1 && i++ < end - start)
        num >>= 1;

    return i == end - start;
}

network build_network(int start, int end, int broadcast, int cidr) {
    network net = {start, end, broadcast, cidr};
    return net;
}

int find_power_bigger_than(int num) {
    for (int i = 0; i < 32; i++) 
        if (pow(2, i) >= num)
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

char *int2ip(int bits) {
    char *ip = (char *)malloc(16 * sizeof(char));
    int last, dots = 0, sum = 0;

    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            last = bits & 1;
            sum += last * pow(2, j);
            bits >>= 1;
        }

        sprintf(ip + i * 3 + dots, "%d", sum);
        if (dots < 3) {
            ip[i * 3 + dots + 1] = '.';
            dots++;
        }

        sum = 0;
    }

    return ip;
}

int ip2int(char ip[]) {
    size_t i = 0;
    int sum = 0;

    while (i++ < strlen(ip))
        if (ip[i] != '.')
            sum = sum * 2 + (ip[i] - '0');

    return sum;
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
