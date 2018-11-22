#include "selection.h"
#include "../utils/swap.h"

void
selection_sort(int *arr, int len)
{
    int i, j, *min;

    for (i = 0; i < len - 1; i++)
    {
        min = &arr[i];

        for (j = i + 1; j < len; j++)
        {
            if (arr[j] < *min)
            {
                min = &arr[j];
            }
        }
        swap(&arr[i], min);
    }
}
