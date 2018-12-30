#include <stdlib.h>
#include <assert.h>
#include "stack.h"

stack_t*
stack_create()
{
    stack_t *stack = malloc(sizeof(stack_t));
    assert(stack);
    stack->top = NULL;

    return stack;
}

static stack_node_t*
create_node(int value)
{
    stack_node_t *node = malloc(sizeof(stack_node_t));
    assert(node);
    node->value = value;
    node->next = NULL;

    return node;
}

void
stack_push(stack_t *stack, int value)
{
    stack_node_t *node = create_node(value);
    node->next = stack->top;
    stack->top = node;
}

int
stack_pop(stack_t *stack)
{
    assert(stack->top != NULL);
    stack_node_t *tmp = stack->top;
    stack->top = tmp->next;
    int value = tmp->value;
    free(tmp);

    return value;
}

void
stack_destroy(stack_t *stack)
{
    while (stack->top != NULL)
    {
        stack_pop(stack);
    }
    free(stack);
}
