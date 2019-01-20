#include "bubble.h"
#include "swap.h"

void
bubble_sort(int *arr, int len)
{
    int i, swaps;

    do
    {
        swaps = 0;

        for (i = 0; i < len - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                swaps++; // number of swaps that occurred within this iteration
            }
        }
        len--;
    }
    while (swaps);
}
