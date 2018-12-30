#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include "utils.h"

static void test_stack(stack_t *stack, int *data, int size);

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
    stack_t *stack = stack_create();

    // perform tests
    test_stack(stack, data, size);

    // cleanup
    stack_destroy(stack);
    free(data);

    return 0;
}

static void
test_stack(stack_t *stack, int *data, int size)
{
    printf("Testing stack operations... ");

    int i, value;
    int *expected_values = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
    {
        stack_push(stack, data[i]);
        expected_values[size - i - 1] = data[i];
    }

    for (i = 0; i < size; i++)
    {
        value = stack_pop(stack);

        if (value != expected_values[i])
        {
            printf("FAIL! Expected: %i; Actual: %i;\n", expected_values[i], value);
            free(expected_values);
            return;
        }
    }
    free(expected_values);
    puts("SUCCESS");
}
