#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../utils/utils.h"
#include "splay.h"

#define TRUE (1)
#define FALSE (0)

static void test_random_insertion(st_t *tree, int *data, int size);
static void test_random_search(st_t *tree, int *data, int size);
static void test_random_deletion(st_t *tree, int *data, int size);
static void test_all_zig_zig_splay(); // Fig. 5. (a) from the original paper
static void test_all_zig_zag_splay(); // Fig. 5. (b) from the original paper

int main(int argc, char **argv)
{
    if (!validate_arguments(argc, argv))
    {
        return 1;
    }
    // declare variables
    st_t *tree;

    // perform tests that use random data
    int size = atoi(argv[1]);
    int *data = malloc(sizeof(int) * size);
    assert(data);
    generate_random_data_sequence(data, argc, argv);
    tree = st_create();
    
    test_random_insertion(tree, data, size);
    test_random_search(tree, data, size);
    test_random_deletion(tree, data, size);
    st_destroy(tree);
    free(data);

    // perform tests that use non-random data:
    test_all_zig_zig_splay();
    test_all_zig_zag_splay();

    return 0;
}

static st_node_t*
bst_search(st_t *tree, int value)
{
    int direction;
    st_node_t *current = tree->root;

    while (current != NULL)
    {
        if (current->value == value)
        {
            return current;
        }
        direction = value > current->value;
        current = current->link[direction];
    }

    return NULL;
}

static st_node_t*
create_node(int value)
{
    st_node_t *node = malloc(sizeof(st_node_t));
    assert(node);

    node->value = value;
    node->link[0] = NULL; // left child
    node->link[1] = NULL; // right child

    return node;
}

static void
link_node(st_node_t *parent, st_node_t *child, int direction)
{
    parent->link[direction] = child;
}

static st_node_t*
bst_insert_internal(st_node_t *node, int value)
{
    if (node == NULL)
    {
        return create_node(value);
    }
    int direction = value > node->value;
    node->link[direction] = bst_insert_internal(node->link[direction], value);

    return node;
}

static void
bst_insert(st_t *tree, int value)
{
    tree->root = bst_insert_internal(tree->root, value);
}

static st_t*
create_all_zig_zig_tree()
{
    int i;
    st_node_t *node;
    st_t *tree = st_create();
    tree->root = create_node(100);

    for (node = tree->root, i = 0; i <= 6; node = node->link[0], i++)
    {
        link_node(node, create_node(node->value - 10), 0);
        link_node(node, create_node(node->value + 5), 1);
    }

    return tree;
}

static st_t*
create_all_zig_zig_tree_expectation()
{
    st_t *tree = st_create();
    
    bst_insert(tree, 40);
    bst_insert(tree, 30);
    bst_insert(tree, 90);
    bst_insert(tree, 70);
    bst_insert(tree, 100);
    bst_insert(tree, 95);
    bst_insert(tree, 105);
    bst_insert(tree, 50);
    bst_insert(tree, 80);
    bst_insert(tree, 45);
    bst_insert(tree, 60);
    bst_insert(tree, 75);
    bst_insert(tree, 85);
    bst_insert(tree, 55);
    bst_insert(tree, 65);

    return tree;
}

static st_t*
create_all_zig_zag_tree()
{
    st_t *tree = st_create();

    bst_insert(tree, 110);
    bst_insert(tree, 115);
    bst_insert(tree, 20);
    bst_insert(tree, 15);
    bst_insert(tree, 100);
    bst_insert(tree, 60);
    bst_insert(tree, 105);
    bst_insert(tree, 50);
    bst_insert(tree, 90);
    bst_insert(tree, 95);
    bst_insert(tree, 70);
    bst_insert(tree, 65);
    bst_insert(tree, 80);
    bst_insert(tree, 75);
    bst_insert(tree, 85);

    return tree;
}

static st_t*
create_all_zig_zag_tree_expectation()
{
    st_t *tree = st_create();

    bst_insert(tree, 80);
    bst_insert(tree, 20);
    bst_insert(tree, 110);
    bst_insert(tree, 15);
    bst_insert(tree, 60);
    bst_insert(tree, 100);
    bst_insert(tree, 115);
    bst_insert(tree, 50);
    bst_insert(tree, 70);
    bst_insert(tree, 90);
    bst_insert(tree, 105);
    bst_insert(tree, 65);
    bst_insert(tree, 75);
    bst_insert(tree, 85);
    bst_insert(tree, 95);

    return tree;
}

static int
compare_nodes(st_node_t *expected, st_node_t *actual)
{
    if (expected == NULL || actual == NULL)
    {
        return expected == actual ? TRUE : FALSE;
    }

    if (expected->value != actual->value)
    {
        return FALSE;
    }

    return (compare_nodes(expected->link[0], actual->link[0]) && compare_nodes(expected->link[1], actual->link[1]));
}

static int
compare_trees(st_t *expected, st_t *actual)
{
    return compare_nodes(expected->root, actual->root);
}

static void
test_random_insertion(st_t *tree, int *data, int size)
{
    printf("Testing random insertion... ");
    for (int i = 0; i < size; i++)
    {
        st_insert(tree, data[i]);

        if (tree->root->value != data[i])
        {
            printf("FAIL! @st_insert(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_random_search(st_t *tree, int *data, int size)
{
    st_node_t *node;

    printf("Testing random search... ");
    for (int i = 0; i < size; i++)
    {
        // test if existing values can be found
        node = st_search(tree, data[i]);

        if (node == NULL) {
            printf("FAIL! @st_search(tree, %i)\n", data[i]);
            return;
        }

        // test if missing values cannot be found
        node = st_search(tree, data[i] * -1);

        if (node != NULL) {
            printf("FAIL! @st_search(tree, %i)\n", data[i] * -1);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_random_deletion(st_t *tree, int *data, int size)
{
    printf("Testing random deletion... ");
    for (int i = 0; i < size; i++)
    {
        st_delete(tree, data[i]);

        if (bst_search(tree, data[i]) != NULL)
        {
            printf("FAIL! @st_delete(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_all_zig_zig_splay()
{
    printf("Testing splay with all zig-zig steps... ");
    st_t *actual = create_all_zig_zig_tree();
    st_t *expected = create_all_zig_zig_tree_expectation();
    st_search(actual, 40);

    if (compare_trees(expected, actual) == TRUE)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL!\n");
    }
    st_destroy(actual);
    st_destroy(expected);
}

static void
test_all_zig_zag_splay()
{
    printf("Testing splay with all zig-zag steps... ");
    st_t *actual = create_all_zig_zag_tree();
    st_t *expected = create_all_zig_zag_tree_expectation();

    st_search(actual, 80);

    if (compare_trees(expected, actual) == TRUE)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL!\n");
    }
    st_destroy(actual);
    st_destroy(expected);
}
