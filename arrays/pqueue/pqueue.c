#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pqueue.h"
#include "swap.h"

#define PQUEUE_INITIAL_CAPACITY (10)
#define PARENT(index) ((index - 1 ) / 2)
#define LEFT(index) (index * 2 + 1)
#define RIGHT(index) (index * 2 + 2)
#define PRIORITY(queue, index) (queue->elements[index]->priority)
#define SWAP(queue, a, b) {\
    swap(&queue->elements[a]->value, &queue->elements[b]->value);\
    swap(&queue->elements[a]->priority, &queue->elements[b]->priority);\
}
#define EXISTS(queue, index) (index < queue->count)

#ifdef MIN_HEAP
#define HAS_HIGHER_PRIORITY(queue, a, b) (PRIORITY(queue, a) > PRIORITY(queue, b))
#else // max heap
#define HAS_HIGHER_PRIORITY(queue, a, b) (PRIORITY(queue, b) > PRIORITY(queue, a))
#endif

pqueue_t*
pqueue_create()
{
    pqueue_t *queue = malloc(sizeof(pqueue_t));
    assert(queue);
    queue->elements = malloc(sizeof(pqueue_el_t*) * PQUEUE_INITIAL_CAPACITY);
    assert(queue->elements);
    queue->count = 0;
    queue->capacity = PQUEUE_INITIAL_CAPACITY;

    return queue;
}

static pqueue_el_t*
create_element(int value, int priority)
{
    pqueue_el_t *element = malloc(sizeof(pqueue_el_t));
    assert(element);
    element->value = value;
    element->priority = priority;

    return element;
}

void
pqueue_insert(pqueue_t *queue, int value, int priority)
{
    pqueue_el_t *element = create_element(value, priority);
    
    if (queue->count + 1 > queue->capacity)
    {
        // allocate more memory to be able to store all elements
        queue->capacity *= 2;
        queue->elements = realloc(queue->elements, sizeof(pqueue_el_t*) * queue->capacity);
        assert(queue->elements);
    }
    queue->elements[queue->count] = element;

    // sift up
    for (int current = queue->count; current > 0 && HAS_HIGHER_PRIORITY(queue, current, PARENT(current)); current = PARENT(current))
    {
        SWAP(queue, current, PARENT(current));
    }
    queue->count++;
}

int
pqueue_extract(pqueue_t *queue)
{
    assert(queue->count > 0);
    int value = queue->elements[0]->value;

    if (queue->count > 1)
    {
        SWAP(queue, 0, queue->count - 1); // swap first element with last element
    }
    free(queue->elements[--queue->count]);

    int current = 0;
    int top_priority = 0;

    while (1)
    {
        if (EXISTS(queue, LEFT(current)) && HAS_HIGHER_PRIORITY(queue, LEFT(current), current))
        {
            top_priority = LEFT(current);
        }

        if (EXISTS(queue, RIGHT(current)) && HAS_HIGHER_PRIORITY(queue, RIGHT(current), top_priority))
        {
            top_priority = RIGHT(current);
        }

        if (current == top_priority)
        {
            break;
        }
        SWAP(queue, current, top_priority);
        current = top_priority;
    }

    return value;
}

void
pqueue_destroy(pqueue_t *queue)
{
    while (queue->count != 0)
    {
        pqueue_extract(queue);
    }
    free(queue->elements);
    free(queue);
}

void
pqueue_print(pqueue_t *queue)
{
    printf("queue: ");

    for (int i = 0; i < queue->count; i++)
    {
        printf("%i (%i); ", queue->elements[i]->value, queue->elements[i]->priority);
    }
    printf("\n");
}
