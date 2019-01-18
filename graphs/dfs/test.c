#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "queue.h"
#include "dfs.h"
#include "repl.h"

int
main(int argc, char **argv)
{
    graph_t *graph = NULL;
    command_t *command;
    print_usage_details();

    while (1)
    {
        command = getcmd();

        if (command->id == COMMAND_UNKNOWN)
        {
            fprintf(stderr, "Unknown command specified.");
            break;
        }
        else if (command->id == COMMAND_CREATE)
        {
            if (graph != NULL)
            {
                graph_destroy(graph);
            }
            graph = graph_create(command->args[0]);
        }
        else if (command->id == COMMAND_CONNECT)
        {
            graph_add_edge(graph, command->args[0], command->args[1]);
        }
        else if (command->id == COMMAND_DISCONNECT)
        {
            graph_del_edge(graph, command->args[0], command->args[1]);
        }
        else if (command->id == COMMAND_DFS)
        {
            queue_t *results = dfs(graph, command->args[0]);
            queue_node_t *node = results->head;
            printf("DFS: ");

            while (node != NULL)
            {
                printf("%i; ", node->value);
                node = node->next;
            }
            printf("\n");
            queue_destroy(results);
        }
        if (command->id == COMMAND_QUIT)
        {
            free(command);
            break;
        }

        free(command);
    }
    graph_destroy(graph);

    return 0;
}
