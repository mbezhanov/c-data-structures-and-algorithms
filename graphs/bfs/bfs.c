#include <stdlib.h>
#include <assert.h>
#include "bfs.h"

#define FALSE (0)
#define TRUE (1)

queue_t*
bfs(graph_t *graph, int node)
{
    queue_t* results = queue_create();
    queue_t* queue = queue_create();
    int *visited = calloc(graph->nodes, sizeof(int));
    assert(visited);
    queue_node_t *curr;
    int value;

    queue_enqueue(queue, node);
    visited[node] = TRUE;

    while (queue->head != NULL)
    {
        value = queue_dequeue(queue);
        queue_enqueue(results, value);
        curr = graph->adjacency_list[value]->head;

        while (curr != NULL)
        {
            if (visited[curr->value] == FALSE)
            {
                queue_enqueue(queue, curr->value);
                visited[curr->value] = TRUE;
            }
            curr = curr->next;
        }
    }
    queue_destroy(queue);
    free(visited);

    return results;
}
