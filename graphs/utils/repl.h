#ifndef REPL_H
#define REPL_H

#define COMMAND_UNKNOWN (-1)
#define COMMAND_QUIT (0)
#define COMMAND_CREATE (1)
#define COMMAND_CONNECT (2)
#define COMMAND_DISCONNECT (3)
#define COMMAND_BFS (4)
#define COMMAND_DFS (5)
#define COMMAND_SINGLE_SOURCE_SHORTEST_PATH (6)
#define COMMAND_ALL_PAIRS_SHORTEST_PATH (7)

typedef struct command_s {
    int id;
    int args[3];
} command_t;

void print_usage_details();
command_t* getcmd();

#endif // REPL_H
