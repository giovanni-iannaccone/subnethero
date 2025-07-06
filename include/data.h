#pragma once

#define NO_DEVICES -1

typedef enum {
    flat_approach,
    flsm_approach,
    vlsm_approach
} approaches;

typedef struct {
    int start;
    int end;
    
    int broadcast;

    int cidr;
} network;