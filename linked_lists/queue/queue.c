#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "queue.h"

queue_t*
queue_create(size_t datasize)
{
    queue_t *queue = malloc(sizeof(queue_t));
    assert(queue);
    queue->head = queue->tail = NULL;
    queue->datasize = datasize;

    return queue;
}

static queue_node_t*
create_node(void *data, size_t datasize)
{
    queue_node_t *node = malloc(sizeof(queue_node_t));
    assert(node);
    node->data = malloc(datasize);
    assert(node->data);
    assert(memcpy(node->data, data, datasize));
    node->next = NULL;

    return node;
}

void
queue_enqueue(queue_t *queue, void *data)
{
    queue_node_t *node = create_node(data, queue->datasize);

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

void
queue_dequeue(queue_t *queue, void *data)
{
    assert(queue->head != NULL);
    queue_node_t *tmp = queue->head;
    assert(memcpy(data, tmp->data, queue->datasize));
    queue->head = tmp->next;
    free(tmp->data);
    free(tmp);
}

void
queue_destroy(queue_t *queue)
{
    void *dummy = malloc(queue->datasize);

    while (queue->head != NULL)
    {
        queue_dequeue(queue, dummy);
    }
    free(dummy);
    free(queue);
}
