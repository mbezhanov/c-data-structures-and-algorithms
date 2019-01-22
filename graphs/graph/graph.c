#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

graph_t*
graph_create(int size)
{
    graph_t *graph = malloc(sizeof(graph_t) * size);
    assert(graph);
    graph->adjacency_list = malloc(sizeof(queue_t*) * size);
    assert(graph->adjacency_list);
    graph->size = size;

    for (int i = 0; i < size; i++)
    {
        graph->adjacency_list[i] = queue_create(sizeof(int) * 2);
    }

    return graph;
}

void
graph_add_edge(graph_t *graph, int from, int to, int weight)
{
    int data[2] = {to, weight};
    queue_enqueue(graph->adjacency_list[from], data);
}

void
graph_del_edge(graph_t *graph, int from, int to)
{
    int data[2];
    queue_node_t *prev = NULL;
    queue_node_t *curr = graph->adjacency_list[from]->head;

    while (curr != NULL)
    {
        memcpy(data, curr->data, sizeof(int) * 2);

        if (data[0] == to)
        {
            if (prev != NULL)
            {
                prev->next = curr->next;
            }
            else
            {
                graph->adjacency_list[from]->head = curr->next;
            }
            free(curr->data);
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
    for (int i = 0; i < graph->size; i++)
    {
        queue_destroy(graph->adjacency_list[i]);
    }
    free(graph->adjacency_list);
    free(graph);
}
