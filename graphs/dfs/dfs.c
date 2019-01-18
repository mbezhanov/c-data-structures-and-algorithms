#include <stdlib.h>
#include <assert.h>
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
    queue_enqueue(results, value);
    queue_node_t *node = graph->adjacency_list[value]->head;

    while (node != NULL)
    {
        dfs_internal(graph, results, visited, node->value);
        node = node->next;
    }
}

queue_t*
dfs(graph_t *graph, int node)
{
    queue_t *results = queue_create();
    int *visited = calloc(graph->nodes, sizeof(int));
    assert(visited);

    dfs_internal(graph, results, visited, node);
    free(visited);

    return results;
}
