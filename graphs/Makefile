CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIRS=../linked_lists/queue ../linked_lists/stack ../arrays/pqueue ../arrays/utils ./bfs ./dfs ./dijkstra ./floyd-warshall ./graph ./utils ../utils
space=$() $()
VPATH=$(subst $(space),:,$(INCLUDE_DIRS))
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIRS))

all: test

test: testgraphs.o queue.o graph.o bfs.o dfs.o dijkstra.o floydwarshall.o stack.o pqueue.o swap.o repl.o readline.o
	$(CC) $(CFLAGS) -o $@ $^
testgraphs.o: testgraphs.c graph.h queue.h bfs.h dfs.h dijkstra.h floydwarshall.h repl.h
queue.o: queue.c queue.h
stack.o: stack.c stack.h
graph.o: graph.c graph.h queue.h
bfs.o: bfs.c bfs.h graph.h queue.h
dfs.o: dfs.c dfs.h graph.h queue.h
dijkstra.o: dijkstra.c dijkstra.h graph.h queue.h pqueue.h stack.h
floydwarshall.o: floydwarshall.c floydwarshall.h graph.h queue.h
repl.o: repl.c repl.h readline.h
readline.o: readline.c readline.h
pqueue.o: pqueue.c pqueue.h swap.h
	$(CC) $(CFLAGS) -DMIN_HEAP -c -o $@ $<
swap.o: swap.c swap.h

clean:
	$(RM) test *.o
