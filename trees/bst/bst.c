#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "bst.h"

#define LEFT (0)
#define RIGHT (1)

#define TRUE (1)
#define FALSE (0)

bst_t*
bst_create()
{
    bst_t *tree = malloc(sizeof(bst_t));
    assert(tree);
    tree->root = NULL;

    return tree;
}

static bst_node_t*
create_node(int value)
{
    bst_node_t *node = malloc(sizeof(bst_node_t));
    assert(node);
    node->value = value;
    node->link[LEFT] = node->link[RIGHT] = NULL;

    return node;
}

static bst_node_t*
bst_insert_internal(bst_node_t *parent, int value)
{
    if (parent == NULL)
    {
        return create_node(value);
    }

    if (parent->value == value)
    {
        return parent; // value already in tree, we don't insert it twice
    }
    int direction = value > parent->value; // 0 = left; 1 = right;
    parent->link[direction] = bst_insert_internal(parent->link[direction], value);

    return parent;
}

void
bst_insert(bst_t *tree, int value)
{
    tree->root = bst_insert_internal(tree->root, value);   
}

static bst_node_t*
inorder_predecessor(bst_node_t *node)
{
    bst_node_t *current = node->link[LEFT];

    while (current->link[RIGHT] != NULL)
    {
        current = current->link[RIGHT];
    }

    return current;
}

static bst_node_t*
bst_delete_internal(bst_node_t *parent, int value)
{
    if (parent == NULL)
    {
        return parent;
    }

    if (parent->value == value)
    {
        if (parent->link[LEFT] == NULL || parent->link[RIGHT] == NULL)
        {
            bst_node_t *child = (parent->link[LEFT] == NULL) ? parent->link[RIGHT] : parent->link[LEFT];
            free(parent);

            return child;            
        }
        bst_node_t *child = inorder_predecessor(parent);
        value = parent->value = child->value;
    }
    int direction = value > parent->value; // 0 = left; 1 = right;
    parent->link[direction] = bst_delete_internal(parent->link[direction], value);

    return parent;
}

void
bst_delete(bst_t *tree, int value)
{
    tree->root = bst_delete_internal(tree->root, value);
}

bst_node_t*
bst_search(bst_t *tree, int value)
{
    int direction;
    bst_node_t *current = tree->root;

    while (current != NULL && current->value != value)
    {
        direction = value > current->value; // 0 = left; 1 = right;
        current = current->link[direction];
    }

    return current;
}

void
bst_destroy(bst_t *tree)
{
    while (tree->root != NULL)
    {
        bst_delete(tree, tree->root->value);
    }
    free(tree);
}

static int
bst_assert_valid_internal(bst_node_t *parent)
{
    if (parent == NULL)
    {
        return TRUE;
    }

    // check if any of the children violate the BST properties
    for (int direction = LEFT; direction <= RIGHT; direction++)
    {
        bst_node_t *child = parent->link[direction];

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
    }
    int left_validity = bst_assert_valid_internal(parent->link[LEFT]);
    int right_validity = bst_assert_valid_internal(parent->link[LEFT]);

    if (left_validity == FALSE || right_validity == FALSE)
    {
        return FALSE;
    }

    return TRUE;
}

int
bst_assert_valid(bst_t *tree)
{
    return bst_assert_valid_internal(tree->root);
}

static void
bst_print_internal(bst_node_t *node, int depth)
{
    for (int i = 0; i < depth; i++)
    {
        putchar(' ');
    }

    if (node == NULL)
    {
        printf("[NULL]\n");
    }
    else
    {
        printf("[v: %i]\n", node->value);
        depth++;
        bst_print_internal(node->link[LEFT], depth);
        bst_print_internal(node->link[RIGHT], depth);
    }
}

void
bst_print(bst_t *tree)
{
    bst_print_internal(tree->root, 0);
}