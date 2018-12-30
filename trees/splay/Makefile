CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test_iterative test_recursive

test_iterative: test.o splay_iterative.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test_recursive: test.o splay_recursive.o utils.o
	$(CC) $(CFLAGS) -D SPLAY_RECURSIVE -o $@ $^
test.o: test.c utils.h splay.h
splay_iterative.o: splay.c splay.h
	$(CC) $(CFLAGS) -c -o $@ $<
splay_recursive.o: splay.c splay.h
	$(CC) $(CFLAGS) -D SPLAY_RECURSIVE -c -o $@ $<
utils.o: utils.c utils.h

clean:
	$(RM) ./test_iterative ./test_recursive *.o
