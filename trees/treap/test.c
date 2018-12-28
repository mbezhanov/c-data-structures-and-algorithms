#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../utils/utils.h"
#include "treap.h"

static void test_insertion(treap_t *tree, int *data, int size);
static void test_search(treap_t *tree, int *data, int size);
static void test_deletion(treap_t *tree, int *data, int size);

int main(int argc, char **argv)
{
    if (!validate_arguments(argc, argv))
    {
        return 1;
    }
    // init variables
    int size = atoi(argv[1]);
    int *data = malloc(sizeof(int) * size);
    assert(data);
    generate_random_data_sequence(data, argc, argv);
    treap_t *tree = treap_create();

    // perform tests
    test_insertion(tree, data, size);
    test_search(tree, data, size);
    test_deletion(tree, data, size);

    // cleanup
    treap_destroy(tree);
    free(data);
}

static void
test_insertion(treap_t *tree, int *data, int size)
{
    printf("Testing insertion... ");
    for (int i = 0; i < size; i++)
    {
        treap_insert(tree, data[i]);

        if (!treap_assert_valid(tree))
        {
            printf("FAIL! @treap_insert(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_search(treap_t *tree, int *data, int size)
{
    treap_node_t *node;

    printf("Testing search... ");
    for (int i = 0; i < size; i++)
    {
        // test if existing values can be found
        node = treap_search(tree, data[i]);

        if (node == NULL)
        {
            printf("FAIL! @treap_search(tree, %i)\n", data[i]);
            return;
        }

        // test if missing values cannot be found
        node = treap_search(tree, data[i] * -1);

        if (node != NULL)
        {
            printf("FAIL! @treap_search(tree, %i)\n", data[i] * -1);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deletion(treap_t *tree, int *data, int size)
{
    printf("Testing deletion... ");
    for (int i = 0; i < size; i++)
    {
        treap_delete(tree, data[i]);

        if (!treap_assert_valid(tree))
        {
            printf("FAIL! @treap_delete(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}
