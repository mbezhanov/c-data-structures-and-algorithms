#ifndef PQUEUE_H
#define PQUEUE_H

typedef struct pqueue_el_s pqueue_el_t;
typedef struct pqueue_s pqueue_t;

struct pqueue_el_s {
    int value;
    int priority;
};

struct pqueue_s {
    pqueue_el_t **elements;
    int count;    // number of nodes currently stored in the priority queue
    int capacity; // total number of nodes the priority queue can hold
};

// core functions
pqueue_t* pqueue_create(void);
void pqueue_insert(pqueue_t *queue, int value, int priority);
int pqueue_extract(pqueue_t *queue); // extract a value from the top of the queue
void pqueue_destroy(pqueue_t *queue);

// helper functions
void pqueue_print(pqueue_t *queue);

#endif // PQUEUE_H
