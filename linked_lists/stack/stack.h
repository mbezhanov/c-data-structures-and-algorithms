#ifndef STACK_H
#define STACK_H

typedef struct stack_node_s stack_node_t;
typedef struct stack_s stack_t;

struct stack_node_s {
    int value;
    stack_node_t *next;
};

struct stack_s {
    stack_node_t *top;
};

stack_t* stack_create();
void stack_push(stack_t *stack, int value);
int stack_pop(stack_t *stack);
void stack_destroy(stack_t *stack);

#endif // STACK_H
