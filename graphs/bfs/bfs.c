#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bfs.h"

#define FALSE (0)
#define TRUE (1)

queue_t*
bfs(graph_t *graph, int node)
{
    size_t datasize = sizeof(int);
    queue_t* results = queue_create(datasize);
    queue_t* queue = queue_create(datasize);
    int *visited = calloc(graph->size, datasize);
    assert(visited);
    queue_node_t *curr;
    int value;

    queue_enqueue(queue, &node);
    visited[node] = TRUE;

    while (queue->head != NULL)
    {
        queue_dequeue(queue, &value);
        queue_enqueue(results, &value);
        curr = graph->adjacency_list[value]->head;

        while (curr != NULL)
        {
            memcpy(&value, curr->data, datasize);

            if (visited[value] == FALSE)
            {
                queue_enqueue(queue, &value);
                visited[value] = TRUE;
            }
            curr = curr->next;
        }
    }
    queue_destroy(queue);
    free(visited);

    return results;
}
