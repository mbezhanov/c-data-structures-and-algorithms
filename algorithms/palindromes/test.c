#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "palindromes.h"

char* getword();

int
main(int argc, char **argv)
{
    char *word;

    while ((word = getword()) != NULL)
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

char*
getword()
{
    int pos = 0;
    int len = 10; // initial line buffer length
    char c;
    char *buffer = malloc(sizeof(char) * len);
    assert(buffer);
    printf("Input a word: ");

    while ((c = getchar()) != '\n')
    {
        if (pos >= len - 1)
        {
            len *= 2;
            buffer = realloc(buffer, len);
        }
        buffer[pos++] = c;
    }

    if (pos == 0) // empty line
    {
        free(buffer);
        return NULL;
    }
    buffer[pos] = '\0';

    return buffer;
}
