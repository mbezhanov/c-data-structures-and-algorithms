#include <stdlib.h>
#include <stdio.h>
#include "fibonacci.h"

int
main(int argc, char **argv)
{
    printf("Fibonacci sequence: ");

    for (int i = 0; i <= 35; i++)
    {
        printf("%i; ", fibonacci(i));
    }
    printf("\n");

    return 0;
}
