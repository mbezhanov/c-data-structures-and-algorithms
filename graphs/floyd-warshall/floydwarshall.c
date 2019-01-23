#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "floydwarshall.h"

#define SQUARE(n) (n * n)
#define ARRAY_SET(arr, width, row, col, value) (arr[row * width + col] = value)
#define ARRAY_GET(arr, width, row, col) (arr[row * width + col])
#define VALUE (0)
#define WEIGHT (1)
#define NONE (-1)

static apspinfo_t*
create_apspinfo_struct(graph_t *graph)
{
    apspinfo_t *apsp = malloc(sizeof(apspinfo_t));
    assert(apsp);
    apsp->dist = malloc(sizeof(int) * SQUARE(graph->size));
    assert(apsp->dist);
    apsp->next = malloc(sizeof(int) * SQUARE(graph->size));
    assert(apsp->next);
    apsp->len = graph->size;

    // initialize "dist" and "next" tables
    for (int row = 0; row < graph->size; row++)
    {
        for (int col = 0; col < graph->size; col++)
        {
            int value = ((row == col) ? 0 : INT_MAX);
            ARRAY_SET(apsp->dist, graph->size, row, col, value);
            ARRAY_SET(apsp->next, graph->size, row, col, NONE);
        }
        queue_node_t *curr = graph->adjacency_list[row]->head;

        while (curr != NULL)
        {
            int data[2];
            memcpy(data, curr->data, sizeof(int) * 2);
            ARRAY_SET(apsp->dist, graph->size, row, data[VALUE], data[WEIGHT]);
            ARRAY_SET(apsp->next, graph->size, row, data[VALUE], row);
            curr = curr->next;
        }
    }

    return apsp;
}

apspinfo_t*
floyd_warshall(graph_t *graph)
{
    apspinfo_t* apsp = create_apspinfo_struct(graph);

    int from, through, to; // vertices
    int distance_candidate, d1, d2;

    for (through = 0; through < graph->size; through++)
    {
        for (from = 0; from < graph->size; from++)
        {
            for (to = 0; to < graph->size; to++)
            {
                d1 = ARRAY_GET(apsp->dist, graph->size, from, through);
                d2 = ARRAY_GET(apsp->dist, graph->size, through, to);

                if (d1 == INT_MAX || d2 == INT_MAX)
                {
                    continue; // a path "from->through->to" does not exist!
                }
                distance_candidate = d1 + d2; 

                if (distance_candidate < ARRAY_GET(apsp->dist, graph->size, from, to)) // compare distance candidate with current distance
                {
                    ARRAY_SET(apsp->dist, graph->size, from, to, distance_candidate);
                    ARRAY_SET(apsp->next, graph->size, from, to, through);
                }
            }
        }
    }

    return apsp;
}

static void
print_path(apspinfo_t *apsp, int from, int to)
{
    int prev, next;
    size_t datasize = sizeof(int);
    queue_t *path = queue_create(datasize);

    for (prev = NONE, next = from; next != prev; prev = next, next = ARRAY_GET(apsp->next, apsp->len, prev, to))
    {
        queue_enqueue(path, &next);
    }
    queue_enqueue(path, &to);

    while (path->head != NULL)
    {
        queue_dequeue(path, &next);
        printf("%i", next);

        if (path->head != NULL)
        {
            printf("->");
        }
    }
    queue_destroy(path);
}

void
floyd_warshall_print(apspinfo_t *apsp)
{
    printf("All-Pairs Shortest Path:\n\n");

    for (int from = 0; from < apsp->len; from++)
    {
        for (int to = 0; to < apsp->len; to++)
        {
            if (from == to)
            {
                continue;
            }
            int distance = ARRAY_GET(apsp->dist, apsp->len, from, to);

            if (distance == INT_MAX)
            {
                continue;
            }
            printf("%i->%i = %i (path: ", from, to, distance);
            print_path(apsp, from, to);
            printf(")\n");
        }
    }
}
