#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "deque.h"
#include "utils.h"

static void test_deque_push_front_pop_front(deque_t *deque, int *data, int size);
static void test_deque_push_front_pop_back(deque_t *deque, int *data, int size);
static void test_deque_push_back_pop_front(deque_t *deque, int *data, int size);
static void test_deque_push_back_pop_back(deque_t *deque, int *data, int size);
static void test_deque_push_mixed_pop_mixed(deque_t *deque, int *data, int size);

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
    deque_t *deque = deque_create();

    // perform tests
    test_deque_push_front_pop_front(deque, data, size);
    test_deque_push_front_pop_back(deque, data, size);
    test_deque_push_back_pop_front(deque, data, size);
    test_deque_push_back_pop_back(deque, data, size);
    test_deque_push_mixed_pop_mixed(deque, data, size);

    // cleanup
    deque_destroy(deque);
    free(data);

    return 0;
}

static void
test_deque_push_front_pop_front(deque_t *deque, int *data, int size)
{
    printf("Testing front pushing with front popping... ");

    int i, value;
    int expected_values[size];

    for (i = 0; i < size; i++)
    {
        deque_push_front(deque, data[i]);
        expected_values[size - i - 1] = data[i];
    }

    for (i = 0; i < size; i++)
    {
        value = deque_pop_front(deque);

        if (value != expected_values[i])
        {
            printf("FAIL! Expected: %i; Actual: %i;\n", expected_values[i], value);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deque_push_front_pop_back(deque_t *deque, int *data, int size)
{
    printf("Testing front pushing with back popping... ");

    int i, value;

    for (i = 0; i < size; i++)
    {
        deque_push_front(deque, data[i]);
    }

    for (i = 0; i < size; i++)
    {
        value = deque_pop_back(deque);

        if (value != data[i])
        {
            printf("FAIL! Expected: %i; Actual: %i;\n", data[i], value);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deque_push_back_pop_front(deque_t *deque, int *data, int size)
{
    printf("Testing back pushing with front popping... ");

    int i, value;

    for (i = 0; i < size; i++)
    {
        deque_push_back(deque, data[i]);
    }

    for (i = 0; i < size; i++)
    {
        value = deque_pop_front(deque);

        if (value != data[i])
        {
            printf("FAIL! Expected: %i; Actual: %i;\n", data[i], value);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deque_push_back_pop_back(deque_t *deque, int *data, int size)
{
    printf("Testing back pushing with back popping... ");

    int i, value;
    int expected_values[size];

    for (i = 0; i < size; i++)
    {
        deque_push_back(deque, data[i]);
        expected_values[size - i - 1] = data[i];
    }

    for (i = 0; i < size; i++)
    {
        value = deque_pop_back(deque);

        if (value != expected_values[i])
        {
            printf("FAIL! Expected: %i; Actual: %i;\n", expected_values[i], value);
            return;
        }
    }
    puts("SUCCESS");
}

static void
test_deque_push_mixed_pop_mixed(deque_t *deque, int *data, int size)
{
    printf("Testing randomly mixed pushing and popping... ");

    int i, destination, actual_value, expected_value, loc;
    int expected_values[size];
    int start = 0;
    int len = 0;

    for (i = 0; i < size; i++, len++)
    {
        destination = rand() % 2;

        if (destination == 0)
        {
            if (start == 0)
            {
                start = size - 1;
            }
            else
            {
                start--;
            }
            loc = start;
            deque_push_front(deque, data[i]);
        }
        else
        {
            loc = (start + len) % size;
            deque_push_back(deque, data[i]);
        }
        expected_values[loc] = data[i];
    }

    for (i = 0; i < size; i++, len--)
    {
        destination = rand() % 2;

        if (destination == 0)
        {
            loc = start;
            actual_value = deque_pop_front(deque);
            start = (start + 1) % size;
        }
        else
        {
            loc = (start + (len - 1)) % size;
            actual_value = deque_pop_back(deque);
        }
        expected_value = expected_values[loc];

        if (actual_value != expected_value)
        {
            printf("FAIL! Expected: %i; Actual: %i;\n", expected_value, actual_value);
            return;
        }
    }
    puts("SUCCESS");
}
