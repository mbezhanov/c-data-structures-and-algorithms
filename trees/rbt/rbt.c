#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rbt.h"

#define COLOR_RED (0)
#define COLOR_BLACK (1)

#define RED_VIOLATION_NONE (-1)

rbt_t*
rbt_create()
{
    rbt_t *tree = malloc(sizeof(rbt_t));
    assert(tree);
    tree->root = NULL;

    return tree;
}

static rbt_node_t*
create_node(int value)
{
    rbt_node_t *node = malloc(sizeof(rbt_node_t));
    assert(node);

    node->value = value;
    node->color = COLOR_RED;
    node->link[0] = NULL; // left child
    node->link[1] = NULL; // right child

    return node;
}

static int
get_color(rbt_node_t *node)
{
    if (node == NULL || node->color != COLOR_RED)
    {
        return COLOR_BLACK;
    }

    return COLOR_RED;
}

static void
set_color(rbt_node_t *node, int color)
{
    if (node != NULL)
    {
        node->color = color;
    }
}

static int
is_red(rbt_node_t *node)
{
    return get_color(node) == COLOR_RED;
}

static int
check_red_violation(rbt_node_t *node, int direction)
{
    if (is_red(node))
    {
        if (is_red(node->link[direction]))
        {
            return direction;
        }
        else if (is_red(node->link[!direction]))
        {
            return !direction;
        }
    }

    return RED_VIOLATION_NONE;
}

static rbt_node_t*
color_flip(rbt_node_t *parent)
{
    set_color(parent, COLOR_RED);
    set_color(parent->link[0], COLOR_BLACK);
    set_color(parent->link[1], COLOR_BLACK);

    return parent;
}

static rbt_node_t*
rotate_single(rbt_node_t *parent, int direction)
{
    rbt_node_t *child = parent->link[!direction];
    parent->link[!direction] = child->link[direction];
    child->link[direction] = parent;
    set_color(parent, COLOR_RED);
    set_color(child, COLOR_BLACK);

    return child; // after rotation, "child" becomes parent of "parent"
}

static rbt_node_t*
rotate_double(rbt_node_t *parent, int direction)
{
   parent->link[!direction] = rotate_single(parent->link[!direction], !direction);

   return rotate_single(parent, direction);
}

static rbt_node_t*
rbt_insert_internal(rbt_node_t *node, int value)
{
    if (node == NULL)
    {
        return create_node(value);
    }

    if (value == node->value)
    {
        return node; // we only allow unique values in the tree
    }

    // insert
    int direction = (value > node->value);
    node->link[direction] = rbt_insert_internal(node->link[direction], value);

    // balance
    int violation = check_red_violation(node->link[direction], direction);

    if (violation == RED_VIOLATION_NONE)
    {
        return node;
    }
    rbt_node_t *aunt = node->link[!direction];

    if (get_color(aunt) == COLOR_RED)
    {
        node = color_flip(node); // Case 1
    }
    else if (violation == direction)
    {
        node = rotate_single(node, !direction); // Case 2
    }
    else if (violation == !direction)
    {
        node = rotate_double(node, !direction); // Case 3
    }

    return node;
}

void
rbt_insert(rbt_t *tree, int value)
{
    tree->root = rbt_insert_internal(tree->root, value);

    if (tree->root->color == COLOR_RED)
    {
        tree->root->color = COLOR_BLACK;
    }
}

static void
fix_colors(rbt_node_t *grandparent, int direction)
{
    set_color(grandparent, COLOR_RED);
    set_color(grandparent->link[0], COLOR_BLACK);
    set_color(grandparent->link[1], COLOR_BLACK);
    set_color(grandparent->link[direction]->link[direction], COLOR_RED);
}

static rbt_node_t*
reverse_color_flip(rbt_node_t *parent)
{
    set_color(parent, COLOR_BLACK);
    set_color(parent->link[0], COLOR_RED);
    set_color(parent->link[1], COLOR_RED);

    return parent;
}

static rbt_node_t*
create_dummy_root(rbt_node_t *real_root)
{
    rbt_node_t *dummy = create_node(0);
    dummy->color = COLOR_BLACK;
    dummy->link[1] = real_root;

    return dummy;
}

void
rbt_delete(rbt_t *tree, int value)
{
    rbt_node_t *dummy = create_dummy_root(tree->root);

    rbt_node_t *grandparent = NULL;
    rbt_node_t *parent = dummy;
    rbt_node_t *current = NULL;
    rbt_node_t *found = NULL;
    int direction = 1; // direction from "parent" to "current"
    int next_direction; // direction from "current" to next child

    for
    (
        current = parent->link[direction]; 
        current != NULL;
        grandparent = parent, parent = current, current = current->link[next_direction], direction = next_direction
    )
    {
        if (current->value == value)
        {
            found = current;
        }
        next_direction = (value > current->value);

        if (is_red(current) || is_red(current->link[next_direction]))
        {
            continue;
        }

        if (is_red(current->link[!next_direction]))
        {
            parent = parent->link[direction] = rotate_single(current, next_direction); // Case 1
            continue;
        }
        rbt_node_t *sibling = parent->link[!direction];

        if (sibling == NULL)
        {
            continue;
        }
        int grandson_direction = grandparent->link[1] == parent; // direction from "grandparent", through "parent", to "current"

        if (is_red(sibling->link[direction]))
        {
            grandparent->link[grandson_direction] = rotate_double(parent, direction); // Case 3
            fix_colors(grandparent->link[grandson_direction], direction);
        }
        else if (is_red(sibling->link[!direction]))
        {
            grandparent->link[grandson_direction] = rotate_single(parent, direction); // Case 4
            fix_colors(grandparent->link[grandson_direction], direction);
        }
        else // both children of "sibling" are black
        {
            reverse_color_flip(parent); // Case 2
        }
    }

    if (found != NULL)
    {
        found->value = parent->value;
        grandparent->link[grandparent->link[1] == parent] = parent->link[parent->link[0] == NULL];
        free(parent);
    }
    tree->root = dummy->link[1];
    free(dummy);
    
    if (get_color(tree->root) == COLOR_RED)
    {
        tree->root->color = COLOR_BLACK;
    }
}

rbt_node_t*
rbt_search(rbt_t *tree, int value)
{
    int direction;
    rbt_node_t *current = tree->root;

    while (current != NULL && current->value != value)
    {
        direction = value > current->value; // 0 = left; 1 = right;
        current = current->link[direction];
    }

    return current;
}

void
rbt_destroy(rbt_t *tree)
{
    while (tree->root != NULL)
    {
        rbt_delete(tree, tree->root->value);
    }
    free(tree);
}

static int
rbt_assert_valid_internal(rbt_node_t *node)
{
    if (node == NULL)
    {
        return 1;
    }

    if (check_red_violation(node, 0) != RED_VIOLATION_NONE || check_red_violation(node, 1) != RED_VIOLATION_NONE)
    {
        fputs("Red violation!\n", stderr);
        return 0;
    }
    rbt_node_t *left_child = node->link[0];
    rbt_node_t *right_child = node->link[1];

    if ((left_child != NULL && left_child->value >= node->value) || (right_child != NULL && right_child->value <= node->value))
    {
        fputs("Binary search tree violation!\n", stderr);
        return 0;
    }
    int left_height = rbt_assert_valid_internal(left_child);
    int right_height = rbt_assert_valid_internal(right_child);

    if (left_height == 0 || right_height == 0)
    {
        // there were violations somewhere down the tree, so have them propagate to the top, by returning "0"
        return 0;
    }

    if (left_height != right_height)
    {
        fputs("Black violation! %i %i %i\n", stderr);
        return 0;
    }

    return is_red(node) ? left_height : left_height + 1; // "left_height" == "right_height", so it doesn't matter which one you use here
}

int
rbt_assert_valid(rbt_t *tree)
{
    return rbt_assert_valid_internal(tree->root);
}

static void
rbt_print_internal(rbt_node_t *node, int depth)
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
        printf("[v: %i c: %s]\n", node->value, node != NULL && node->color == COLOR_RED ? "R" : "B");
        depth++;
        rbt_print_internal(node->link[0], depth);
        rbt_print_internal(node->link[1], depth);
    }
}

void
rbt_print(rbt_t *tree)
{
    rbt_print_internal(tree->root, 0);
    puts("--------------------");
}
