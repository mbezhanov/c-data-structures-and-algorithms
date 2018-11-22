#include <stdlib.h>
#include "merge.h"

static void
merge(int *arr, int start, int mid, int end)
{
    int i, j, k;
    int len = end - start + 1; // length of the temporary array
    int *tmp = malloc(sizeof(int) * len);

    // create a temporary array, where the elements are sorted in ascending order
    for (i = start, j = mid + 1, k = 0; k < len; k++)
    {
        if (j > end)
        {
            tmp[k] = arr[i++];
        }
        else if (i > mid)
        {
            tmp[k] = arr[j++];
        }
        else if (arr[j] < arr[i])
        {
            tmp[k] = arr[j++];
        }
        else
        {
            tmp[k] = arr[i++];
        }
    }

    // copy the sorted elements from the temporary array into the original array
    for (i = start, k = 0; k < len; i++, k++)
    {
        arr[i] = tmp[k];
    }

    // free the temporary array
    free(tmp);
}

void
merge_sort(int *arr, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}
