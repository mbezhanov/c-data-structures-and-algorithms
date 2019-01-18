#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "readline.h"

#ifndef READLINE_PROMPT
#define READLINE_PROMPT ">"
#endif

char*
readline()
{
    int pos = 0;
    int len = 10; // initial line buffer length
    char c;
    char *buffer = malloc(sizeof(char) * len);
    assert(buffer);
    printf("%s ", READLINE_PROMPT);

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
