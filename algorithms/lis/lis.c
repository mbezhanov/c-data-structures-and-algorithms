#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lis.h"

#define NONE (-1)

static int
array_max_index(int *arr, int size)
{
    assert(arr);
    int index = 0;
    int max = arr[index];

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
            index = i;
        }
    }

    return index;
}

static lis_t*
create_subsequence(int *arr, int *len, int *prev, int size)
{
    int last = array_max_index(len, size);
    int length = len[last];

    lis_t *subsequence = malloc(sizeof(lis_t));
    assert(subsequence);
    subsequence->arr = malloc(sizeof(int) * length);
    assert(subsequence->arr);
    subsequence->len = length;
    
    for (int i = length - 1; i >= 0; i--)
    {
        subsequence->arr[i] = arr[last];
        last = prev[last];
    }

    return subsequence;
}

lis_t*
longest_increasing_subsequence(int *arr, int size)
{
    int len[size];
    int prev[size];
    int i, j;

    for (i = 0; i < size; i++)
    {
        prev[i] = NONE;
        len[i] = 1;

        for (j = 0; j < i; j++)
        {
            if (arr[j] < arr[i] && len[j] >= len[i])
            {
                prev[i] = j;
                len[i]++;
            }
        }
    }

    return create_subsequence(arr, len, prev, size);
}
