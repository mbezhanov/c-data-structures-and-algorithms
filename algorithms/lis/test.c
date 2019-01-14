#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lis.h"
#include "utils.h"

static void
array_print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%i; ", arr[i]);
    }
    printf("\n");
}

int
main(int argc, char **argv)
{
    if (!validate_arguments(argc, argv))
    {
        return 1;
    }
    // init variables
    int size = atoi(argv[1]);
    int *arr = malloc(sizeof(int) * size);
    assert(arr);
    generate_random_data_sequence(arr, argc, argv);
    
    // find and print the longest increasing subsequence
    lis_t *subsequence = longest_increasing_subsequence(arr, size);
    printf("\nLongest increasing subsequence: ");
    array_print(subsequence->arr, subsequence->len);
    printf("Length: %i elements\n", subsequence->len);

    // cleanup
    free(subsequence->arr);
    free(subsequence);
    free(arr);

    return 0;
}
