#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "rbt.h"

static void
print_usage_details(const char *command)
{
    fprintf(stderr, "Usage: %s [arguments]\n\n", command);
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  size      Number of nodes to insert into the tree.\n");
    fprintf(stderr, "  seed      An int for seeding the random number generator (default: 1)\n");
    fprintf(stderr, "  interval  Interval between subsequent node values (default: 5)\n");
}

static void
test_insertion(rbt_t *tree, int *data, int size)
{
    printf("Testing insertion... ");
    for (int i = 0; i < size; i++)
    {
        rbt_insert(tree, data[i]);

        if (!rbt_assert_valid(tree)) {
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

        if (node == NULL) {
            printf("FAIL! @rbt_search(tree, %i)\n", data[i]);
            return;
        }

        // test if missing values cannot be found
        node = rbt_search(tree, data[i] * -1);

        if (node != NULL) {
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

        if (!rbt_assert_valid(tree)) {
            printf("FAIL! @rbt_delete(tree, %i)\n", data[i]);
            return;
        }
    }
    puts("SUCCESS");
}

static void 
generate_random_data_sequence(int *arr, int size, int seed, int interval)
{
    int i, r, tmp;

    // fill array with numbers in ascending order
    for (i = 0; i < size; i++)
    {
        arr[i] = (i + 1) * interval;
    }

    // shuffle array
    srand(seed);
    i--;

    while (i >= 0)
    {
        r = rand() % size;
        tmp = arr[i];
        arr[i] = arr[r];
        arr[r] = tmp;
        i--;
    }

    // print the generated sequence
    printf("Sequence: ");

    for (i = 0; i < size; i++)
    {
        printf("%i; ", arr[i]);
    }
    printf("\n");
}

int
main(int argc, char **argv)
{
    int size, seed, interval, *data;

    if (argc < 2)
    {
        print_usage_details(argv[0]);
        return 1;
    }
    // parse arguments
    size = atoi(argv[1]);
    seed = (argc >= 3) ? atoi(argv[2]) : 1;
    interval = (argc >= 4) ? atoi(argv[3]) : 5;

    // init variables
    data = malloc(sizeof(data) * size);
    assert(data);
    rbt_t *tree = rbt_create();

    // perform tests
    generate_random_data_sequence(data, size, seed, interval);
    test_insertion(tree, data, size);
    test_search(tree, data, size);
    test_deletion(tree, data, size);

    // cleanup
    rbt_destroy(tree);
    free(data);

    return 0;
}
