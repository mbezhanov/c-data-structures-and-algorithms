#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "dijkstra.h"
#include "pqueue.h"
#include "stack.h"

#define FALSE (0)
#define TRUE (1)

#define NONE (-1)

#define VALUE (0)
#define WEIGHT (1)

static spinfo_t*
create_spinfo_struct(int start, int size)
{
    spinfo_t *sp = malloc(sizeof(spinfo_t));
    sp->start = start;
    sp->visited = calloc(size, sizeof(int));
    sp->prev = malloc(sizeof(int) * size);
    sp->dist = malloc(sizeof(int) * size);
    sp->len = size;
    
    assert(sp);
    assert(sp->visited);
    assert(sp->prev);
    assert(sp->dist);

    for (int i = 0; i < size; i++)
    {
        sp->dist[i] = INT_MAX;
        sp->prev[i] = NONE;
    }

    return sp;
}

spinfo_t*
dijkstra(graph_t *graph, int start)
{
    pqueue_t *pqueue = pqueue_create();
    spinfo_t *sp = create_spinfo_struct(start, graph->size);
    sp->dist[start] = 0;
    pqueue_insert(pqueue, start, sp->dist[start]);

    int value, distance_candidate;
    int data[2]; // data[0] = value; data[1] = weight; (of a node stored in the adjacency list)

    while (pqueue->count != 0)
    {
        value = pqueue_extract(pqueue);
        sp->visited[value] = TRUE;
        
        for (queue_node_t *curr = graph->adjacency_list[value]->head; curr != NULL; curr = curr->next)
        {
            memcpy(data, curr->data, sizeof(int) * 2);
            distance_candidate = sp->dist[value] + data[WEIGHT];

            if (distance_candidate < sp->dist[data[VALUE]])
            {
                sp->dist[data[VALUE]] = distance_candidate;
                sp->prev[data[VALUE]] = value;
                pqueue_insert(pqueue, data[VALUE], sp->dist[data[VALUE]]);
            }
        }
    }
    pqueue_destroy(pqueue);

    return sp;
}

static void
print_path(spinfo_t *sp, int to)
{
    stack_t *stack = stack_create();
    
    while (to != NONE)
    {
        stack_push(stack, to);
        to = sp->prev[to];
    }
    
    while (stack->top != NULL)
    {
        printf("%i", stack_pop(stack));

        if (stack->top != NULL)
        {
            printf("->");
        }
    }
    stack_destroy(stack);
}

void
dijkstra_print(spinfo_t *sp)
{
    printf("Single-Source Shortest Paths:\n\n");

    for (int i = 0; i < sp->len; i++)
    {
        if (i == sp->start)
        {
            continue;
        }
        printf("%i->%i ", sp->start, i);

        if (sp->visited[i] == FALSE)
        {
            printf("(unreachable)");
        }
        else
        {
            printf("= %i (path: ", sp->dist[i]);
            print_path(sp, i);
            printf(")");
        }
        printf("\n");
    }
}
