#include "data.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NETIP       1
#define CSV         2
#define BROADCAST   3
#define START       4
#define END         5

void export_csv(FILE *csv, network networks[], int n);
int parse_csv(FILE *csv, network **networks);