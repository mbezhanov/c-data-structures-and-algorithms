#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

// a struct for storing shortest path information
typedef struct spinfo_s {
    int start;
    int *visited;
    int *prev;
    int *dist;
    int len;
} spinfo_t;

// core function
spinfo_t* dijkstra(graph_t *graph, int start);

// helper functions
void print_shortest_paths(spinfo_t *sp);

#endif // DIJKSTRA_H
