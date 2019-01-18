#include <stdlib.h>
#include <stdio.h>
#include "readline.h"
#include "palindromes.h"

int
main(int argc, char **argv)
{
    char *word;

    while ((word = readline()) != NULL)
    {
        printf("\"%s\" is ", word);

        if (!is_palindrome(word))
        {
            printf("not ");
        }
        printf("a palindrome\n\n");
        free(word);
    }
}
