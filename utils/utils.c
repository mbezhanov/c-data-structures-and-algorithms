#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#ifndef DS_NAME
#define DS_NAME "data structure"
#endif

#ifndef DS_CONSTITUENTS_NAME
#define DS_CONSTITUENTS_NAME "nodes"
#endif

static void
print_usage_details(const char *command)
{
    fprintf(stderr, "Usage: %s [arguments]\n\n", command);
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  size      Number of %s to insert into the %s.\n", DS_CONSTITUENTS_NAME, DS_NAME);
    fprintf(stderr, "  seed      An int for seeding the random number generator (default: 1)\n");
    fprintf(stderr, "  interval  Interval between subsequent node values (default: 5)\n");
}

int
validate_arguments(int argc, char **argv)
{
    if (argc < 2)
    {
        print_usage_details(argv[0]);
        return 0; // "0" = false
    }
    return 1; // "1" = true
}

static void 
generate_random_data_sequence_internal(int *arr, int size, int seed, int interval)
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

void
generate_random_data_sequence(int *arr, int argc, char **argv)
{
    // parse arguments
    int size = atoi(argv[1]);
    int seed = (argc >= 3) ? atoi(argv[2]) : 1;
    int interval = (argc >= 4) ? atoi(argv[3]) : 5;

    generate_random_data_sequence_internal(arr, size, seed, interval);
}
