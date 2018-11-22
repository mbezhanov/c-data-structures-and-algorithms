#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "sort.h"

static void
print_usage_details(const char *command)
{
    fprintf(stderr, "Usage: %s [arguments]\n\n", command);
    fprintf(stderr, "Arguments:\n");
    fprintf(stderr, "  len       Number of integers to insert into an array for sorting.\n");
    fprintf(stderr, "  seed      An int for seeding the random number generator (default: 1)\n");
    fprintf(stderr, "  interval  Interval between subsequent values (default: 7)\n");
}

static void
array_print(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%i; ", arr[i]);
    }
    printf("\n");
}

static void
array_fill_random(int *arr, int size, int seed, int interval)
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
}

static int*
set_up(int *original, int len)
{
    int *sorted = malloc(sizeof(int) * len);
    assert(sorted);
    memcpy(sorted, original, sizeof(int) * len);
    memcpy(sorted, original, len);

    return sorted;
}

static int
assert_sorted(int *sorted, int len)
{
    int failures = 0;

    for (int i = 0; i < len - 1; i++)
    {
        if (sorted[i] > sorted[i + 1])
        {
            failures++;
        }
    }

    return failures;
}

static void
tear_down(int *original, int *sorted, int len, int failures)
{
    puts(failures == 0 ? "SUCCESS" : "FAIL!");
    printf("Original: ");
    array_print(original, len);
    printf("Sorted: ");
    array_print(sorted, len);
    printf("\n");
    free(sorted);
}

static void
test_bubble_sort(int *original, int len)
{
    printf("Testing bubble sort... ");
    int *sorted = set_up(original, len);
    bubble_sort(sorted, len);
    int failures = assert_sorted(sorted, len);
    tear_down(original, sorted, len, failures);
}

static void
test_heap_sort(int *original, int len)
{
    printf("Testing heap sort... ");
    int *sorted = set_up(original, len);
    heap_sort(sorted, len);
    int failures = assert_sorted(sorted, len);
    tear_down(original, sorted, len, failures);
}

static void
test_insertion_sort(int *original, int len)
{
    printf("Testing insertion sort... ");
    int *sorted = set_up(original, len);
    insertion_sort(sorted, len);
    int failures = assert_sorted(sorted, len);
    tear_down(original, sorted, len, failures);
}

static void
test_selection_sort(int *original, int len)
{
    printf("Testing selection sort... ");
    int *sorted = set_up(original, len);
    selection_sort(sorted, len);
    int failures = assert_sorted(sorted, len);
    tear_down(original, sorted, len, failures);
}

static void
test_merge_sort(int *original, int len)
{
    printf("Testing merge sort... ");
    int *sorted = set_up(original, len);
    merge_sort(sorted, 0, len - 1);
    int failures = assert_sorted(sorted, len);
    tear_down(original, sorted, len, failures);
}

static void
test_quick_sort(int *original, int len)
{
    printf("Testing quick sort... ");
    int *sorted = set_up(original, len);
    quick_sort(sorted, 0, len - 1);
    int failures = assert_sorted(sorted, len);
    tear_down(original, sorted, len, failures);
}

int
main(int argc, char** argv)
{
    int len, seed, interval, *arr;

    if (argc < 2)
    {
        print_usage_details(argv[0]);
        return 1;
    }
    // parse command-line arguments
    len = atoi(argv[1]);
    seed = (argc >= 3) ? atoi(argv[2]) : 1;
    interval = (argc >= 4) ? atoi(argv[3]) : 5;

    // initialize array
    arr = malloc(sizeof(arr) * len);
    assert(arr);
    array_fill_random(arr, len, seed, interval);

    // test iterative algorithms
    test_bubble_sort(arr, len);
    test_heap_sort(arr, len);
    test_insertion_sort(arr, len);
    test_selection_sort(arr, len);

    // test recursive algorithms
    test_merge_sort(arr, len);
    test_quick_sort(arr, len);

    // free allocated memory
    free(arr);
}
