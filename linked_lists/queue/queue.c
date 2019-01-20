#include <stdlib.h>
#include <assert.h>
#include "queue.h"

queue_t*
queue_create(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    assert(queue);
    queue->head = queue->tail = NULL;

    return queue;
}

static queue_node_t*
create_node(int value)
{
    queue_node_t *node = malloc(sizeof(queue_node_t));
    assert(node);
    node->value = value;
    node->next = NULL;

    return node;
}

void
queue_enqueue(queue_t *queue, int value)
{
    queue_node_t *node = create_node(value);

    if (queue->head == NULL)
    {
        queue->head = node;
    }
    else
    {
        queue->tail->next = node;
    }
    queue->tail = node;
}

int
queue_dequeue(queue_t *queue)
{
    assert(queue->head != NULL);
    queue_node_t *tmp = queue->head;
    int value = tmp->value;
    queue->head = tmp->next;
    free(tmp);

    return value;
}

void
queue_destroy(queue_t *queue)
{
    while (queue->head != NULL)
    {
        queue_dequeue(queue);
    }
    free(queue);
}
