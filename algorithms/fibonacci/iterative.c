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
    int a = 0;
    int b = 1;
    int answer = 0;

    for (int i = 2; i <= n; i++)
    {
        answer = a + b;
        a = b;
        b = answer;
    }

    return answer;
}
