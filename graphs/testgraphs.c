#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "bfs.h"
#include "dfs.h"
#include "dijkstra.h"
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
            free(command);
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
            graph_add_edge(graph, command->args[0], command->args[1], command->args[2] != -1 ? command->args[2] : 0);
        }
        else if (command->id == COMMAND_DISCONNECT)
        {
            graph_del_edge(graph, command->args[0], command->args[1]);
        }
        else if (command->id == COMMAND_BFS)
        {
            int value;
            queue_t *results = bfs(graph, command->args[0]);
            queue_node_t *node = results->head;
            printf("BFS: ");

            while (node != NULL)
            {
                memcpy(&value, node->data, sizeof(int));
                printf("%i; ", value);
                node = node->next;
            }
            printf("\n");
            queue_destroy(results);
        }
        else if (command->id == COMMAND_DFS)
        {
            int value;
            queue_t *results = dfs(graph, command->args[0]);
            queue_node_t *node = results->head;
            printf("DFS: ");

            while (node != NULL)
            {
                memcpy(&value, node->data, sizeof(int));
                printf("%i; ", value);
                node = node->next;
            }
            printf("\n");
            queue_destroy(results);
        }
        else if (command->id == COMMAND_DIJKSTRA)
        {
            spinfo_t *sp = dijkstra(graph, command->args[0]);
            print_shortest_paths(sp);
            free(sp->visited);
            free(sp->dist);
            free(sp->prev);
            free(sp);
        }
        else if (command->id == COMMAND_QUIT)
        {
            free(command);
            break;
        }

        free(command);
    }

    if (graph != NULL)
    {
        graph_destroy(graph);
    }

    return 0;
}
