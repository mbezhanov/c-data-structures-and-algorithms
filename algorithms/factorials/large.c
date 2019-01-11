#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define BUFFER_SIZE (65) // enough to fit the result of at most "50!"

void
print_factorial(unsigned int n)
{
    int buffer[BUFFER_SIZE];
    buffer[0] = 1;

    int i, j, product;
    int carry = 0;
    int len = 1;

    for (i = 2; i <= n; i++)
    {
        for (j = 0; j < len; j++)
        {
            product = i * buffer[j] + carry;
            carry = product / 10;
            buffer[j] = product % 10;
        }

        while (carry > 0)
        {
            buffer[len++] = carry % 10;
            carry /= 10;
        }
    }

    for (i = len - 1; i >= 0; i--)
    {
        printf("%i", buffer[i]);
    }
}

int
main(int argc, char **argv)
{
    for (int i = 1; i <= 50; i++)
    {
        printf("%i! = ", i);
        print_factorial(i);
        printf("\n");
    }

    return 0;
}
