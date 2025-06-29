#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

#include "../include/flat.h"
#include "../include/flsm.h"
#include "../include/vlsm.h"

#define BOLD_BLUE   "\033[1;34m"
#define GREEN       "\033[32m"
#define RED         "\033[31m"
#define RESET       "\033[0m"

int assert(bool condition, const char *name) {
    if (condition)
        printf("%s [+] %s %s\n", GREEN, name, RESET);
    else
        printf("%s [-] %s %s\n", RED, name, RESET);

    return !condition;
}

int test_all_1() {
    int num = 240;
    return all_1(num, 24, 28) && !all_1(num, 25, 30);
}

int test_ip_to_int() {
    char ip[] = "192.168.1.0";
    return strcmp(ip, int2ip(ip2int(ip))) == 0;
}

int main() {
    printf("%s STARTING TESTS %s\n", BOLD_BLUE, RESET);

    assert(test_all_1(), "all 1");
    assert(test_ip_to_int(), "ip to int conversion");

    printf("\n");
    return 0;
}