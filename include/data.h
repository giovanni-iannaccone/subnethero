#pragma once

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