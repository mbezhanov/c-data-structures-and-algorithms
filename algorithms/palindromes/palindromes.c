#include <string.h>
#include "palindromes.h"

#define TRUE (1)
#define FALSE (0)

int
is_palindrome(const char *str)
{
    int i, cmp;
    int len = strlen(str);

    for (i = 0; i < len / 2; i++)
    {
        cmp = len - 1 - i;

        if (str[i] != str[cmp])
        {
            return FALSE;
        }
    }

    return TRUE;
}
