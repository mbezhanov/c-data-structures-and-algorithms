CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIRS=../linked_lists/queue ./bfs ./dfs ./graph ./utils ../utils
space=$() $()
VPATH=$(subst $(space),:,$(INCLUDE_DIRS))
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIRS))

all: test

test: testgraphs.o queue.o graph.o bfs.o dfs.o repl.o readline.o
	$(CC) $(CFLAGS) -o $@ $^
testgraphs.o: testgraphs.c graph.h queue.h bfs.h dfs.h repl.h
queue.o: queue.c queue.h
graph.o: graph.c graph.h queue.h
bfs.o: bfs.c bfs.h graph.h queue.h
dfs.o: dfs.c dfs.h graph.h queue.h
repl.o: repl.c repl.h readline.h
readline.o: readline.c readline.h

clean:
	$(RM) test *.o
