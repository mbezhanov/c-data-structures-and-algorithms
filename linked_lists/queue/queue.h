#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct queue_node_s queue_node_t;
typedef struct queue_s queue_t;

struct queue_node_s {
    void *data;
    queue_node_t *next;
};

struct queue_s {
    queue_node_t *head;
    queue_node_t *tail;
    size_t datasize;
};

queue_t* queue_create(size_t datasize);
void queue_enqueue(queue_t *queue, void *data);
void queue_dequeue(queue_t *queue, void *data);
void queue_destroy(queue_t *queue);

#endif // QUEUE_H
