#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../utils/utils.h"
#include "bst.h"

static void test_insertion(bst_t *tree, int *data, int size);
static void test_search(bst_t *tree, int *data, int size);
static void test_deletion(bst_t *tree, int *data, int size);

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
    bst_t *tree = bst_create();

    // perform tests
    test_insertion(tree, data, size);
    test_search(tree, data, size);
    test_deletion(tree, data, size);

    // cleanup
    bst_destroy(tree);
    free(data);
}

static void
test_insertion(bst_t *tree, int *data, int size)
{
    printf("Testing insertion... ");
    for (int i = 0; i < size; i++)
    {
        bst_insert(tree, data[i]);

        if (!bst_assert_valid(tree))
        {
            printf("FAIL! @bst_insert(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_search(bst_t *tree, int *data, int size)
{
    bst_node_t *node;

    printf("Testing search... ");
    for (int i = 0; i < size; i++)
    {
        // test if existing values can be found
        node = bst_search(tree, data[i]);

        if (node == NULL)
        {
            printf("FAIL! @bst_search(tree, %i)\n", data[i]);
            return;
        }

        // test if missing values cannot be found
        node = bst_search(tree, data[i] * -1);

        if (node != NULL)
        {
            printf("FAIL! @bst_search(tree, %i)\n", data[i] * -1);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deletion(bst_t *tree, int *data, int size)
{
    printf("Testing deletion... ");
    for (int i = 0; i < size; i++)
    {
        bst_delete(tree, data[i]);

        if (!bst_assert_valid(tree))
        {
            printf("FAIL! @bst_delete(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}
