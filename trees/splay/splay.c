#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "splay.h"

#ifdef SPLAY_RECURSIVE
#   define SPLAY(tree, value) splay_recursive(tree, value)
#else
#   define SPLAY(tree, value) splay_iterative(tree, value)
#endif

#define DUMMY_VALUE (-1)
#define LEFT (0)
#define RIGHT (1)

st_t*
st_create()
{
    st_t *tree = malloc(sizeof(st_t));
    assert(tree);
    tree->root = NULL;

    return tree;
}

static st_node_t*
create_node(int value)
{
    st_node_t *node = malloc(sizeof(st_node_t));
    assert(node);

    node->value = value;
    node->link[LEFT] = NULL; // left child
    node->link[RIGHT] = NULL; // right child

    return node;
}

static st_node_t*
rotate(st_node_t *parent, int direction)
{
    st_node_t *child = parent->link[!direction];
    parent->link[!direction] = child->link[direction];
    child->link[direction] = parent;

    return child; // after rotation, "child" becomes parent of "parent"
}

static st_node_t*
splay_recursive_internal(st_node_t *grandparent, int value)
{
    if (grandparent == NULL || grandparent->value == value)
    {
        return grandparent;
    }
    int direction = value > grandparent->value; // 0 = left; 1 = right;
    st_node_t *parent = grandparent->link[direction];

    if (parent == NULL)
    {
        return grandparent;
    }

    if (parent->value == value)
    {
        return rotate(grandparent, !direction); // Case 1
    }
    int grandchild_direction = value > parent->value; // 0 = left; 1 = right;
    st_node_t *grandchild = parent->link[grandchild_direction] = splay_recursive_internal(parent->link[grandchild_direction], value);

    if (grandchild != NULL)
    {
        if (grandchild_direction != direction)
        {
            grandparent->link[direction] = rotate(parent, !grandchild_direction); // first rotation in Case 3
        }
        else
        {
            grandparent = rotate(grandparent, !direction); // first rotation in Case 2
        }
    }

    if (grandparent->link[direction] != NULL)
    {
        return rotate(grandparent, !direction); // second rotation in Case 2 or Case 3
    }

    return grandparent;
}

static void
splay_recursive(st_t *tree, int value)
{
    tree->root = splay_recursive_internal(tree->root, value);
}

static void
splay_iterative(st_t *tree, int value)
{
    if (tree->root == NULL)
    {
        return; // tree is empty, do nothing
    }
    st_node_t *grandparent = tree->root; // aka "current node" in the loop below
    st_node_t *left, *right; // left and right subtrees
    st_node_t *dummy = create_node(DUMMY_VALUE); // dummy tree root

    left = right = dummy;

    for (;;) {
        if (grandparent->value == value)
        {
            break; // node found!
        }
        int direction = value > grandparent->value; // 0 = left; 1 = right;
        st_node_t *parent = grandparent->link[direction];

        if (parent == NULL)
        {
            break;
        }
        int grandchild_direction = value > parent->value;

        if (parent->value != value) // ensure "parent" is not the node we're looking for
        {
            if (direction == grandchild_direction)
            {
                st_node_t *grandchild = parent->link[grandchild_direction];

                // node is more than two steps away, in straight direction, from the current node, so perform a rotation
                if (grandchild != NULL && grandchild->value != value)
                {
                    grandparent = rotate(grandparent, !direction);
                }

                if (grandparent->link[direction] == NULL)
                {
                    break;
                }
            }
        }

        if (direction == LEFT) // add current node as leftmost child of the right subtree
        {
            right->link[LEFT] = grandparent;
            right = grandparent;
        }
        else  // add current node as rightmost child of the left subtree
        {
            left->link[RIGHT] = grandparent;
            left = grandparent;
        }
        grandparent = grandparent->link[direction];
    }
    // reassemble the tree:
    left->link[RIGHT] = grandparent->link[LEFT];
    right->link[LEFT] = grandparent->link[RIGHT];
    grandparent->link[LEFT] = dummy->link[RIGHT];
    grandparent->link[RIGHT] = dummy->link[LEFT];
    free(dummy);

    tree->root = grandparent;
}

void
st_insert(st_t *tree, int value)
{
    if (tree->root == NULL)
    {
        tree->root = create_node(value);
        return;
    }

    SPLAY(tree, value);

    if (tree->root->value == value)
    {
        return; // value is already in the tree, so we don't have to do anything
    }
    st_node_t *node = create_node(value);
    int direction = value > tree->root->value; // 0 = left; 1 = right;
    node->link[direction] = tree->root->link[direction];
    node->link[!direction] = tree->root;
    tree->root->link[direction] = NULL;
    tree->root = node;
}

void
st_delete(st_t *tree, int value)
{
    if (tree->root == NULL)
    {
        return; // tree is already empty, so there is nothing to delete
    }

    SPLAY(tree, value);

    if (tree->root->value != value)
    {
        return; // value is already not in the tree, so we don't have to do anything else
    }

    // remove node and join orphaned subtrees
    st_node_t *node = tree->root;

    if (tree->root->link[LEFT] == NULL)
    {
        tree->root = node->link[RIGHT];
    }
    else
    {
        SPLAY(tree, tree->root->link[LEFT]->value);
        tree->root->link[RIGHT] = node->link[RIGHT];
    }
    free(node);
}

st_node_t*
st_search(st_t *tree, int value)
{
    SPLAY(tree, value);

    if (tree->root != NULL && tree->root->value == value)
    {
        return tree->root;
    }

    return NULL;
}

void
st_destroy(st_t *tree)
{
    while (tree->root != NULL)
    {
        st_delete(tree, tree->root->value);
    }
    free(tree);
}

static void
st_print_internal(st_node_t *node, int depth)
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
        printf("[v: %i]\n", node->value);
        st_print_internal(node->link[0], depth);
        st_print_internal(node->link[1], depth);
    }
}

void
st_print(st_t *tree)
{
    st_print_internal(tree->root, 0);
}
