#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "treap.h"

#define PRIORITY_MIN (1000)
#define PRIORITY_MAX (9999)

#define LEFT (0)
#define RIGHT (1)

#define TRUE (1)
#define FALSE (0)

treap_t*
treap_create()
{
    treap_t *tree = malloc(sizeof(treap_t));
    assert(tree);
    tree->root = NULL;

    return tree;   
}

static int                                                                                                                                  
random_number_between(int min, int max)                                                                                                     
{                                                                                                                                           
    return (rand() % ((max + 1) - min) + min);                                                                                              
}

static treap_node_t*
create_node(int value)
{
    treap_node_t *node = malloc(sizeof(treap_node_t));
    assert(node);
    node->value = value;
    node->priority = random_number_between(PRIORITY_MIN, PRIORITY_MAX);
    node->link[LEFT] = NULL;
    node->link[RIGHT] = NULL;

    return node;
}

static treap_node_t*
rotate(treap_node_t *parent, int direction)
{
    treap_node_t *child = parent->link[!direction];
    parent->link[!direction] = child->link[direction];
    child->link[direction] = parent;

    return child; // child becomes the new parent
}

static treap_node_t*
treap_insert_internal(treap_node_t *parent, int value)
{
    if (parent == NULL)
    {
        return create_node(value);
    }

    if (parent->value == value)
    {
        return parent; // value already exists in tree, so we don't insert it twice
    }
    int direction = value > parent->value; // 0 = left; 1 = right;
    parent->link[direction] = treap_insert_internal(parent->link[direction], value);

    if (parent->link[direction]->priority > parent->priority)
    {
        parent = rotate(parent, !direction);
    }

    return parent; 
}

void
treap_insert(treap_t *tree, int value)
{
    tree->root = treap_insert_internal(tree->root, value);
}

static treap_node_t*
treap_delete_internal(treap_node_t *parent, int value)
{
    if (parent == NULL)
    {
        return parent;
    }

    if (parent->value == value)
    {
        if (parent->link[LEFT] == NULL || parent->link[RIGHT] == NULL) // Case 1 and Case 2
        {
            treap_node_t *child = (parent->link[LEFT] == NULL) ? parent->link[RIGHT] : parent->link[LEFT];
            free(parent);

            return child;
        }
        // find which of the two children has higher priority
        int max = parent->link[RIGHT]->priority > parent->link[LEFT]->priority; // 0 = left; 1 = right;
        parent = rotate(parent, !max);
    }
    int direction = value > parent->value; // 0 = left; 1 = right;
    parent->link[direction] = treap_delete_internal(parent->link[direction], value);    

    return parent;
}

void
treap_delete(treap_t *tree, int value)
{
    tree->root = treap_delete_internal(tree->root, value);
}

treap_node_t *
treap_search(treap_t *tree, int value)
{
    int direction;
    treap_node_t *current = tree->root;

    while (current != NULL && current->value != value)
    {
        direction = value > current->value; // 0 = left; 1 = right;
        current = current->link[direction];
    }

    return current;
}

void
treap_destroy(treap_t *tree)
{
    while (tree->root != NULL)
    {
        treap_delete(tree, tree->root->value);
    }
    free(tree);
}

static int
treap_assert_valid_internal(treap_node_t *parent)
{
    if (parent == NULL)
    {
        return TRUE;
    }

    // check if any of the children violate any of the treap properties
    for (int direction = LEFT; direction <= RIGHT; direction++)
    {
        treap_node_t *child = parent->link[direction];

        if (child == NULL)
        {
            continue;
        }
        int bstViolation = (direction == LEFT) ? child->value >= parent->value : child->value <= parent->value;

        if (bstViolation)
        {
            fputs("Binary search tree violation!\n", stderr);
            return FALSE;
        }

        if (child->priority > parent->priority)
        {
            fputs("Max heap violation!\n", stderr);
            return FALSE;
        }
    }
    // check validity of left and right subtrees
    int left_validity = treap_assert_valid_internal(parent->link[LEFT]);
    int right_validity = treap_assert_valid_internal(parent->link[RIGHT]);

    if (left_validity == FALSE || right_validity == FALSE)
    {
        // there were violations somewhere along the subtrees, so we have them propagate to the top, by returning "0"
        return FALSE;
    }

    return TRUE;
}

int
treap_assert_valid(treap_t *tree)
{
    return treap_assert_valid_internal(tree->root);
}

static void
treap_print_internal(treap_node_t *node, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        putchar(' ');
    }

    if (node == NULL)
    {
        puts("[NULL]");
    }
    else
    {
        depth++;
        printf("[v: %i p: %i]\n", node->value, node->priority);
        treap_print_internal(node->link[LEFT], depth);
        treap_print_internal(node->link[RIGHT], depth);
    }
}

void
treap_print(treap_t *tree)
{
    treap_print_internal(tree->root, 0);
}
