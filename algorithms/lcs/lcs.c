#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "lcs.h"

static int
array_get(int *arr, int row, int col, int width)
{
    return *(arr + col + (row * width));
}

static void
array_set(int *arr, int row, int col, int width, int value)
{
    *(arr + col + (row * width)) = value;
}

static int
max(int a, int b)
{
    return a > b ? a : b;
}

lcs_t*
longest_common_subsequence(char *str1, char *str2)
{
    int row, col, val;
    int rows = strlen(str2) + 1;
    int cols = strlen(str1) + 1;

    int *arr = malloc(sizeof(int) * rows * cols);
    assert(arr);

    // fill the array with solutions
    for (row = 0; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            if (row == 0 || col == 0)
            {
                val = 0;
            }
            else if (str2[row - 1] == str1[col - 1])
            {
                // upper left value + 1
                val = array_get(arr, row - 1, col - 1, cols) + 1;
            }
            else
            {
                // max of upper value and left value
                val = max(array_get(arr, row - 1, col, cols), array_get(arr, row, col - 1, cols));
            }
            array_set(arr, row, col, cols, val);
        }
    }

    // retrieve the actual subsequence
    lcs_t *subsequence = malloc(sizeof(lcs_t));
    assert(subsequence);
    row = rows - 1;
    col = cols - 1;
    int i = subsequence->len = array_get(arr, row, col, cols);
    char *lcs = malloc(sizeof(char) * i + 1);
    assert(lcs);
    lcs[i] = '\0';

    while (row > 0 && col > 0)
    {
        if (str1[col - 1] == str2[row - 1])
        {
            lcs[--i] = str1[col - 1];
            row--;
            col--;
        }
        else
        {
            if (array_get(arr, row - 1, col, cols) > array_get(arr, row, col - 1, cols))
            {
                row--;
            }
            else
            {
                col--;
            }
        }
    }
    subsequence->arr = arr;
    subsequence->str = lcs;

    return subsequence;
}

static int
intlen(int n)
{
    int digits;

    for (digits = 0; n != 0; n /= 10, digits++);

    return digits;
}

void
print_solutions_table(lcs_t *lcs, char *str1, char *str2)
{
    int row = strlen(str2);
    int col = strlen(str1);
    int rows = row + 1;
    int cols = col + 1;
    int cellwidth = intlen(array_get(lcs->arr, rows - 1, col, cols));

    // print header row
    printf("   ");
    for (col = 0; col < cols; col++)
    {
        printf("%-*c", cellwidth + 1, col > 0 ? str1[col - 1] : ' ');
    }
    printf("\n");

    // print table contents
    for (row = 0; row < rows; row++)
    {
        printf("%c  ", row > 0 ? str2[row - 1] : ' ');
        
        for (col = 0; col < cols; col++)
        {
            printf("%0*d ", cellwidth , array_get(lcs->arr, row, col, cols));
        }
        printf("\n");
    }
}
