CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIRS=../../linked_lists/queue ../../utils
space=$() $()
VPATH=$(subst $(space),:,$(INCLUDE_DIRS))
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIRS))

all: test

test: test.o queue.o graph.o dfs.o repl.o readline.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c queue.h graph.h dfs.h repl.h
queue.o: queue.c queue.h
graph.o: graph.c graph.h queue.h
dfs.o: dfs.c dfs.h graph.h queue.h
repl.o: repl.c repl.h readline.h
readline.o: readline.c readline.h

clean:
	$(RM) test *.o
