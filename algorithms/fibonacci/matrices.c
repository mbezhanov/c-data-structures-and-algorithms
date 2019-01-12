#include <assert.h>
#include "fibonacci.h"

static void
multiply(int M1[2][2], int M2[2][2])
{
    int result[2][2];

    // compute multiplication products:
    result[0][0] = (M1[0][0] * M2[0][0]) + (M1[0][1] * M2[1][0]);
    result[0][1] = (M1[0][0] * M2[0][1]) + (M1[0][1] * M2[1][1]);
    result[1][0] = (M1[1][0] * M2[0][0]) + (M1[1][1] * M2[1][0]);
    result[1][1] = (M1[1][0] * M2[0][1]) + (M1[1][1] * M2[1][1]);

    // update the original matrix:
    M1[0][0] = result[0][0];
    M1[0][1] = result[0][1];
    M1[1][0] = result[1][0];
    M1[1][1] = result[1][1];
}

static void
power(int M[2][2], int exponent)
{
    if (exponent <= 1)
    {
        return;
    }
    power(M, exponent / 2);
    multiply(M, M);

    if (exponent % 2 != 0)
    {
        int Q[2][2] = {{1, 1}, {1, 0}};   
        multiply(M, Q);
    }
}

int
fibonacci(int n)
{
    assert(n >= 0);

    if (n <= 1)
    {
        return n;
    }
    int M[2][2] = {{1, 1}, {1, 0}}; // initialize M to the Q-matrix
    power(M, n - 1);

    return M[0][0];
}
