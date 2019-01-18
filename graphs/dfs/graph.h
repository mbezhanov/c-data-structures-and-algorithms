#ifndef GRAPH_H
#define GRAPH_H

#include "queue.h" // a singly linked-list, where we append elements to the tail, and pop elements from the head

typedef struct graph_s graph_t;

struct graph_s {
    queue_t **adjacency_list;
    int nodes; // number of nodes in the graph
};

graph_t* graph_create(int nodes);
void graph_add_edge(graph_t *graph, int a, int b); // create an edge connecting nodes with values "a" and "b"
void graph_del_edge(graph_t *graph, int a, int b); // remove an edge connecting nodes with values "a" and "b"
void graph_destroy(graph_t *graph);

#endif // GRAPH_H
