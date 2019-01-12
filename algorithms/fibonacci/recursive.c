#include <assert.h>
#include "fibonacci.h"

int
fibonacci(int n)
{
    assert(n >= 0);

    if (n <= 1)
    {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}
