#include <stdlib.h>
#include <assert.h>
#include "deque.h"

#define PREV (0)
#define NEXT (1)

#define FRONT (0)
#define BACK (1)

deque_t*
deque_create()
{
    deque_t *deque = malloc(sizeof(deque_t));
    assert(deque);
    deque->boundary[FRONT] = deque->boundary[BACK] = NULL;

    return deque;
}

static deque_node_t*
create_node(int value)
{
    deque_node_t *node = malloc(sizeof(deque_node_t));
    assert(node);
    node->value = value;
    node->link[PREV] = node->link[NEXT] = NULL;

    return node;
}

static void
deque_push(deque_t *deque, int value, int destination)
{
    assert(destination == FRONT || destination == BACK);
    deque_node_t *node = create_node(value);
    int direction = (destination == FRONT); // will resolve to: 0 = PREV OR 1 = NEXT
    node->link[direction] = deque->boundary[destination];

    if (deque->boundary[destination] == NULL)
    {
        deque->boundary[FRONT] = deque->boundary[BACK] = node;
    }
    else
    {
        deque->boundary[destination]->link[!direction] = node;
        deque->boundary[destination] = node;
    }
}

void 
deque_push_front(deque_t *deque, int value)
{
    deque_push(deque, value, FRONT);
}

void 
deque_push_back(deque_t *deque, int value)
{
    deque_push(deque, value, BACK);
}

static int
deque_pop(deque_t *deque, int destination)
{
    assert(destination == FRONT || destination == BACK);
    assert(deque->boundary[destination] != NULL);
    deque_node_t *node = deque->boundary[destination];
    int value = node->value;

    if (deque->boundary[FRONT] == deque->boundary[BACK])
    {
        deque->boundary[FRONT] = deque->boundary[BACK] = NULL;
    }
    else
    {
        int direction = (destination == FRONT); // will resolve to: 0 = PREV OR 1 = NEXT
        deque->boundary[destination] = node->link[direction];
    }
    free(node);

    return value;
}

int
deque_pop_front(deque_t *deque)
{
    return deque_pop(deque, FRONT);
}

int
deque_pop_back(deque_t *deque)
{
    return deque_pop(deque, BACK);
}

void
deque_destroy(deque_t *deque)
{
    while (deque->boundary[FRONT] != NULL)
    {
        deque_pop_front(deque);
    }
    free(deque);
}
