#include "../include/utils.h"

network build_network(int start, int end, int broadcast, int cidr) {
    network net = {start, end, broadcast, cidr};
    return net;
}

int convert_to_int(char ip[15]) {
    int sum = 0;

    for (int i = 0; i < 15; i++)
        if (ip[i] != '.')
            sum = sum * 2 + (ip[i] - '0');
    
    return sum;
}

void convert_to_ip(char ip[15], int bits) {
    int last, dots = 0, sum = 0;

    for (int i = 3; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            last = bits & 1;
            sum += last * pow(2, j);
            bits >>= 1;
        }

        sprintf(ip + i * 3 + dots, "%d", sum);
        if (dots < 3) {
            ip[i * 3 + 1] = '.';
            dots++;
        }

        sum = 0;
    }
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

void sort(int nums[], int n) {
    int temp;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
}
