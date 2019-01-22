#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dfs.h"

#define FALSE (0)
#define TRUE (1)

static void
dfs_internal(graph_t *graph, queue_t *results, int *visited, int value)
{
    if (visited[value] == TRUE)
    {
        return;
    }
    visited[value] = TRUE;
    queue_enqueue(results, &value);
    queue_node_t *node = graph->adjacency_list[value]->head;

    while (node != NULL)
    {
        memcpy(&value, node->data, sizeof(int));
        dfs_internal(graph, results, visited, value);
        node = node->next;
    }
}

queue_t*
dfs(graph_t *graph, int node)
{
    size_t datasize = sizeof(int);
    queue_t *results = queue_create(datasize);
    int *visited = calloc(graph->size, datasize);
    assert(visited);

    dfs_internal(graph, results, visited, node);
    free(visited);

    return results;
}
