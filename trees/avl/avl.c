#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "avl.h"

#define LEFT (0)
#define RIGHT (1)

#define EMPTY_TREE_HEIGHT (-1)

#define TRUE (1)
#define FALSE (0)

avl_t*
avl_create()
{
    avl_t *tree = malloc(sizeof(avl_t));
    assert(tree);
    tree->root = NULL;

    return tree;
}

static avl_node_t*
create_node(int value)
{
    avl_node_t *node = malloc(sizeof(avl_node_t));
    assert(node);
    node->value = value;
    node->height = 0;
    node->link[LEFT] = NULL;
    node->link[RIGHT] = NULL;

    return node;
}

static int
max(int a, int b)
{
    return a > b ? a : b;
}

static int
get_height(avl_node_t *node)
{
    if (node == NULL)
    {
        return EMPTY_TREE_HEIGHT;
    }

    return node->height;
}

static int
compute_height(avl_node_t *node)
{
    return 1 + max(get_height(node->link[LEFT]), get_height(node->link[RIGHT]));
}

static avl_node_t*
rotate(avl_node_t *parent, int direction)
{
    // rotate nodes
    avl_node_t *child = parent->link[!direction];
    parent->link[!direction] = child->link[direction];
    child->link[direction] = parent;

    // update heights
    parent->height = compute_height(parent);
    child->height = compute_height(child);

    return child; // child becomes the new parent
}

static int
has_imbalance(avl_node_t *node)
{
    int height_difference = get_height(node->link[LEFT]) - get_height(node->link[RIGHT]);

    if (height_difference < -1 || height_difference > 1)
    {
        return TRUE;
    }

    return FALSE;
}

static avl_node_t*
avl_insert_internal(avl_node_t *parent, int value)
{
    if (parent == NULL)
    {
        return create_node(value);
    }

    if (parent->value == value)
    {
        return parent; // value already exists in the tree, so we don't insert it twice
    }
    int direction = value > parent->value; // 0 = left; 1 = right;
    parent->link[direction] = avl_insert_internal(parent->link[direction], value);
    parent->height = compute_height(parent); // update the height

    if (has_imbalance(parent))
    {
        int grandchild_direction = value > parent->link[direction]->value; // 0 = left; 1 = right;

        if (direction != grandchild_direction)
        {
            // first rotation in "zig-zag" cases
            parent->link[direction] = rotate(parent->link[direction], !grandchild_direction);
        }
        // second rotation in "zig-zag" cases OR first (and only) rotation in "zig-zig" cases
        parent = rotate(parent, !direction);
    }

    return parent;
}

void
avl_insert(avl_t *tree, int value)
{
    tree->root = avl_insert_internal(tree->root, value);
}

static int
inorder_predecessor_value(avl_node_t *node)
{
    avl_node_t *inorder_predecessor = node->link[LEFT];

    while (inorder_predecessor->link[RIGHT] != NULL)
    {
        inorder_predecessor = inorder_predecessor->link[RIGHT];
    }

    return inorder_predecessor->value;
}

static int
higher_subtree_direction(avl_node_t *parent)
{
    return get_height(parent->link[RIGHT]) > get_height(parent->link[LEFT]); // 0 = left; 1 = right;
}

static int
has_equally_high_subtrees(avl_node_t *node)
{
    return (get_height(node->link[LEFT]) == get_height(node->link[RIGHT]));
}

avl_node_t*
avl_delete_internal(avl_node_t *parent, int value)
{
    if (parent == NULL)
    {
        return parent;
    }

    if (parent->value == value)
    {
        if (parent->link[LEFT] == NULL || parent->link[RIGHT] == NULL)
        {
            avl_node_t *node = (parent->link[LEFT] == NULL) ? parent->link[RIGHT] : parent->link[LEFT];
            free(parent);

            return node;
        }
        value = inorder_predecessor_value(parent);
        parent->value = value;
        parent->link[LEFT] = avl_delete_internal(parent->link[LEFT], value);
    }
    else
    {
        int direction = value > parent->value; // 0 = left; 1 = right;
        parent->link[direction] = avl_delete_internal(parent->link[direction], value);
    }
    parent->height = compute_height(parent); // update height

    if (has_imbalance(parent))
    {
        int imbalance_direction = higher_subtree_direction(parent); // 0 = left; 1 = right;
        
        if (!has_equally_high_subtrees(parent->link[imbalance_direction]))
        {
            int higher_grandchild_direction = higher_subtree_direction(parent->link[imbalance_direction]); // 0 = left; 1 = right;
            
            if (imbalance_direction != higher_grandchild_direction)
            {
                // first rotation in "zig-zag" cases
                parent->link[imbalance_direction] = rotate(parent->link[imbalance_direction], !higher_grandchild_direction);   
            }
        }
        // second rotation in "zig-zag" cases; first rotation in "zig-zig" cases
        parent = rotate(parent, !imbalance_direction);
    }

    return parent;
}

void
avl_delete(avl_t *tree, int value)
{
    tree->root = avl_delete_internal(tree->root, value);
}

avl_node_t*
avl_search(avl_t *tree, int value)
{
    int direction;
    avl_node_t *current = tree->root;

    while (current != NULL && current->value != value)
    {
        direction = value > current->value; // 0 = left; 1 = right;
        current = current->link[direction];
    }

    return current;
}

void
avl_destroy(avl_t *tree)
{
    while (tree->root != NULL)
    {
        avl_delete(tree, tree->root->value);
    }
    free(tree);
}

static int
avl_assert_valid_internal(avl_node_t *parent)
{
    if (parent == NULL)
    {
        return TRUE;
    }

    // check if any of the children violate the BST properties
    for (int direction = LEFT; direction <= RIGHT; direction++)
    {
        avl_node_t *child = parent->link[direction];

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
    
    // check if the AVL height property is violated
    if (has_imbalance(parent))
    {
        fputs("Height difference violation!\n", stderr);
        return FALSE;
    }

    // check the integrity of the "height" metadata:
    int max_height = max(get_height(parent->link[LEFT]), get_height(parent->link[RIGHT]));

    if (parent->height != 1 + max_height)
    {
        fputs("Height metadata corruption!\n", stderr);
        return FALSE;
    }

    // check validity of left and right subtrees
    int left_validity = avl_assert_valid_internal(parent->link[LEFT]);
    int right_validity = avl_assert_valid_internal(parent->link[RIGHT]);

    if (left_validity == FALSE || right_validity == FALSE)
    {
        // there were violations somewhere along the subtrees, so we have them propagate to the top, by returning "0"
        return FALSE;
    }

    return TRUE;
}

int
avl_assert_valid(avl_t *tree)
{
    return avl_assert_valid_internal(tree->root);
}

static void
avl_print_internal(avl_node_t *node, int depth)
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
        printf("[v: %i h: %i]\n", node->value, node->height);
        avl_print_internal(node->link[LEFT], depth);
        avl_print_internal(node->link[RIGHT], depth);
    }
}

void
avl_print(avl_t *tree)
{
    avl_print_internal(tree->root, 0);
}
