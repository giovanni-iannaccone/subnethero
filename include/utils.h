#pragma once

#include <math.h>
#include <stdio.h>

#include "data.h"

network build_network(int start, int end, int broadcast, int cidr);

int convert_to_int(char ip[15]);
void convert_to_ip(char ip[15], int bits);

int find_power_bigger_than(int num);

int get_broadcast(int ip, int cidr);
int get_hostid(int ip, int cidr);
int get_subnet_mask(int cidr);

void sort(int nums[], int n);