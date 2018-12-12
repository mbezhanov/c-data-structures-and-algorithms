#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../utils/utils.h"
#include "rbt.h"

static void test_insertion(rbt_t *tree, int *data, int size);
static void test_search(rbt_t *tree, int *data, int size);
static void test_deletion(rbt_t *tree, int *data, int size);

int
main(int argc, char **argv)
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
    rbt_t *tree = rbt_create();

    // perform tests
    test_insertion(tree, data, size);
    test_search(tree, data, size);
    test_deletion(tree, data, size);

    // cleanup
    rbt_destroy(tree);
    free(data);

    return 0;
}

static void
test_insertion(rbt_t *tree, int *data, int size)
{
    printf("Testing insertion... ");
    for (int i = 0; i < size; i++)
    {
        rbt_insert(tree, data[i]);

        if (!rbt_assert_valid(tree))
        {
            printf("FAIL! @rbt_insert(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_search(rbt_t *tree, int *data, int size)
{
    rbt_node_t *node;

    printf("Testing search... ");
    for (int i = 0; i < size; i++)
    {
        // test if existing values can be found
        node = rbt_search(tree, data[i]);

        if (node == NULL)
        {
            printf("FAIL! @rbt_search(tree, %i)\n", data[i]);
            return;
        }

        // test if missing values cannot be found
        node = rbt_search(tree, data[i] * -1);

        if (node != NULL)
        {
            printf("FAIL! @rbt_search(tree, %i)\n", data[i] * -1);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deletion(rbt_t *tree, int *data, int size)
{
    printf("Testing deletion... ");
    for (int i = 0; i < size; i++)
    {
        rbt_delete(tree, data[i]);

        if (!rbt_assert_valid(tree))
        {
            printf("FAIL! @rbt_delete(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}
