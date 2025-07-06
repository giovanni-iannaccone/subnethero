#include "../include/lookup.h"

unsigned int lookup(network networks[], int n, int ip) {
    int low = 0;
    int high = n;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (ip >= networks[mid].start && ip <= networks[mid].broadcast)
            return networks[mid].start - 1;

        if (ip >= networks[mid].broadcast)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}
