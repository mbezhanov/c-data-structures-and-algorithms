#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "singly.h"

sll_t*
sll_create(void)
{
    sll_t *list = malloc(sizeof(sll_t));
    assert(list);
    list->head = NULL;

    return list;
}

static sll_node_t*
create_node(char *key, char *value)
{
    sll_node_t *node = malloc(sizeof(sll_node_t));
    assert(node);
    node->key = key;
    node->value = value;
    node->next = NULL;

    return node;
}

void
sll_add(sll_t *list, char *key, char *value)
{
    sll_node_t *node = create_node(key, value);
    node->next = list->head;
    list->head = node;
}

void
sll_remove(sll_t *list, char *key)
{
    if (list->head == NULL)
    {
        return;
    }
    sll_node_t *prev, *curr;

    for
    (
        prev = NULL, curr = list->head;
        curr != NULL && strcmp(curr->key, key) != 0;
        prev = curr, curr = curr->next
    );

    if (prev == NULL)
    {
        list->head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }
    free(curr);
}

sll_node_t*
sll_find(sll_t *list, char *key)
{
    sll_node_t *current = list->head;

    while (current != NULL && strcmp(current->key, key) != 0)
    {
        current = current->next;
    }

    return current;
}

void
sll_destroy(sll_t *list)
{
    while (list->head != NULL)
    {
        sll_remove(list, list->head->key);
    }
    free(list);
}

void
sll_print(sll_t *list)
{
    if (list->head == NULL)
    {
        return;
    }

    for (sll_node_t *current = list->head; current != NULL; current = current->next)
    {
        printf("%s => %s; ", current->key, current->value);
    }
}
