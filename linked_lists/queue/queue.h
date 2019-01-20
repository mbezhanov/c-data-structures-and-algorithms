#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_node_s queue_node_t;
typedef struct queue_s queue_t;

struct queue_node_s {
    int value;
    queue_node_t *next;
};

struct queue_s {
    queue_node_t *head;
    queue_node_t *tail;
};

queue_t* queue_create(void);
void queue_enqueue(queue_t *queue, int value);
int queue_dequeue(queue_t *queue);
void queue_destroy(queue_t *queue);

#endif // QUEUE_H
