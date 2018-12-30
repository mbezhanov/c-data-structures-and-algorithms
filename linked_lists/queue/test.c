#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "utils.h"

static void test_queue(queue_t *queue, int *data, int size);

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
    queue_t *queue = queue_create();

    // perform tests
    test_queue(queue, data, size);

    // cleanup
    queue_destroy(queue);
    free(data);

    return 0;
}

static void
test_queue(queue_t *queue, int *data, int size)
{
    printf("Testing queue operations... ");

    int i, value;

    for (i = 0; i < size; i++)
    {
        queue_enqueue(queue, data[i]);
    }

    for (i = 0; i < size; i++)
    {
        value = queue_dequeue(queue);

        if (value != data[i])
        {
            printf("FAIL! Expected: %i; Actual: %i;\n", data[i], value);
            return;
        }
    }
    puts("SUCCESS");
}
