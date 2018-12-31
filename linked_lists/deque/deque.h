#ifndef DEQUE_H
#define DEQUE_H

typedef struct deque_node_s deque_node_t;
typedef struct deque_s deque_t;

struct deque_node_s {
    int value;
    deque_node_t *link[2]; // 0 = previous (closer to the front); 1 = next (closer to the back);
};

struct deque_s {
    deque_node_t *boundary[2]; // pointers to boundary nodes (0 = front; 1 = back;)
};

deque_t* deque_create();
void deque_push_front(deque_t *deque, int value);
void deque_push_back(deque_t *deque, int value);
int deque_pop_front(deque_t *deque);
int deque_pop_back(deque_t *deque);
void deque_destroy(deque_t *deque);

#endif // DEQUE_H
