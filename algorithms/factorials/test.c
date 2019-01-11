#include <stdlib.h>
#include <stdio.h>
#include "factorial.h"

int
main(int argc, char **argv)
{
    for (int i = 1; i <= 12; i++)
    {
        printf("%i! = %i\n", i, factorial(i));
    }

    return 0;
}
