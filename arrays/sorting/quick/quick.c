#include "quick.h"
#include "../utils/swap.h"

void
quick_sort(int *arr, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int i, pi; // "pi" means "pivot index"
    int *pivot = &arr[end];

    for (i = pi = start; i < end; i++)
    {
        if (arr[i] < *pivot)
        {
            swap(&arr[i], &arr[pi++]);
        }
    }
    swap(&arr[pi], pivot);
    quick_sort(arr, start, pi - 1);
    quick_sort(arr, pi + 1, end);
}
