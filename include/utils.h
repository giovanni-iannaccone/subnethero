#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

int all_1(int num, int start, int end);
network build_network(int start, int end, int broadcast, int cidr);

int find_power_bigger_than(int num);

int get_broadcast(int ip, int cidr);
int get_hostid(int ip, int cidr);
int get_subnet_mask(int cidr);

unsigned int ip2int(char ip[]);
char *int2ip(unsigned int bits);

void sort(int nums[], int n);