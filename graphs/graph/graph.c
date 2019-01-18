#include <stdlib.h>
#include <assert.h>
#include "graph.h"

graph_t*
graph_create(int nodes)
{
    graph_t *graph = malloc(sizeof(graph_t) * nodes);
    assert(graph);
    graph->adjacency_list = malloc(sizeof(queue_t*) * nodes);
    graph->nodes = nodes;

    for (int i = 0; i < nodes; i++)
    {
        graph->adjacency_list[i] = queue_create();
    }

    return graph;
}

void
graph_add_edge(graph_t *graph, int a, int b)
{
    queue_enqueue(graph->adjacency_list[a], b);
}

void
graph_del_edge(graph_t *graph, int a, int b)
{
    queue_node_t *prev = NULL;
    queue_node_t *curr = graph->adjacency_list[a]->head;

    while (curr != NULL)
    {
        if (curr->value == b)
        {
            if (prev != NULL)
            {
                prev->next = curr->next;
            }
            else
            {
                graph->adjacency_list[a]->head = curr->next;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

void
graph_destroy(graph_t *graph)
{
    for (int i = 0; i < graph->nodes; i++)
    {
        queue_destroy(graph->adjacency_list[i]);
    }
    free(graph->adjacency_list);
    free(graph);
}
