#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

// struct for storing shortest path information
typedef struct spinfo_s {
    int start;
    int *visited;
    int *prev;
    int *dist;
    int len;
} spinfo_t;

// core functions
spinfo_t* dijkstra(graph_t *graph, int start);

// helper functions
void dijkstra_print(spinfo_t *sp);

#endif // DIJKSTRA_H
