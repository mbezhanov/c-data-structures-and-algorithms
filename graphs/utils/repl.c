#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "readline.h"
#include "repl.h"

void
print_usage_details()
{
    printf("Depth-First Search REPL\n\n");
    printf("Available commands:\n");
    printf("  create NODES            create a new graph consisting of X nodes (e.g. \"create 10\")\n");
    printf("  connect NODE1 NODE2     create a connection between two nodes (e.g. \"connect 0 2\")\n");
    printf("  disconnect NODE1 NODE2  remove connection between two nodes (e.g. \"disconnect 0 2\")\n");
    printf("  bfs NODE                perform BFS starting from a particular node (e.g. \"bfs 0\")\n");
    printf("  dfs NODE                perform DFS starting from a particular node (e.g. \"dfs 0\")\n");
    printf("  quit                    quit the DFS REPL (you can also use \"exit\"\n\n");
}

command_t*
getcmd()
{  
    char *line = readline();
    int linepos = 0;
    int buffpos = 0;
    int len = 10; // initial line buffer length
    int argcnt = 0; // argument counter
    char *buffer = malloc(sizeof(char) * len);
    assert(buffer);
    command_t *command = malloc(sizeof(command_t));

    for (int i = 0; i < 3; i++)
    {
        command->args[i] = -1;
    }

    while (1)
    {
        if (line[linepos] != ' ' && line[linepos] != '\0')
        {
            if (buffpos >= len - 1)
            {
                len *= 2;
                buffer = realloc(buffer, len);
            }
            buffer[buffpos++] = line[linepos++];
            continue;
        }
        buffer[buffpos] = '\0';
        
        if (argcnt == 0)
        {
            if (strcmp(buffer, "create") == 0)
            {
                command->id = COMMAND_CREATE;
            }
            else if (strcmp(buffer, "connect") == 0)
            {
                command->id = COMMAND_CONNECT;
            }
            else if (strcmp(buffer, "disconnect") == 0)
            {
                command->id = COMMAND_DISCONNECT;
            }
            else if (strcmp(buffer, "bfs") == 0)
            {
                command->id = COMMAND_BFS;
            }
            else if (strcmp(buffer, "dfs") == 0)
            {
                command->id = COMMAND_DFS;
            }
            else if (strcmp(buffer, "quit") == 0 || strcmp(buffer, "exit") == 0)
            {
                command->id = COMMAND_QUIT;
            }
            else
            {
                command->id = COMMAND_UNKNOWN;
            }
            argcnt++;
        }
        else if (argcnt <= 3)
        {
            command->args[argcnt - 1] = atoi(buffer);
            argcnt++;
        }

        if (line[linepos] == '\0')
        {
            break;
        }
        else
        {
            buffpos = 0; // reset buffer position
            linepos++;
        }
    }
    free(buffer);
    free(line);

    return command;
}
