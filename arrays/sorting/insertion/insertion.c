#include "insertion.h"

void
insertion_sort(int *arr, int len)
{
    int i, j, curr;

    for (i = 1; i < len; i++)
    {
        curr = arr[i];

        for (j = i - 1; j >= 0 && arr[j] > curr; j--)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = curr;
    }
}
