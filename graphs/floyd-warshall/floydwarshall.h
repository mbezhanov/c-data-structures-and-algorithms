#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "graph.h"

// struct for storing all-pairs shortest path info
typedef struct apspinfo_s {
    int *dist;
    int *next;
    int len;
} apspinfo_t;

// core functions
apspinfo_t* floyd_warshall(graph_t *graph);

// helper functions
void floyd_warshall_print(apspinfo_t *apsp);

#endif // FLOYD_WARSHALL_H
