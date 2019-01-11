#include <assert.h>
#include "factorial.h"

#ifdef FACTORIAL_RECURSIVE
unsigned int
factorial(unsigned int n)
{
    assert(n > 0);

    if (n <= 2)
    {
        return n;
    }

    return n * factorial(n - 1);
}
#endif

#ifdef FACTORIAL_ITERATIVE
unsigned int
factorial(unsigned int n)
{
    assert(n > 0);

    if (n <= 2)
    {
        return n;
    }
    unsigned int f = 2;

    for (int i = 3; i <= n; i++)
    {
        f *= i;
    }

    return f;
}
#endif
