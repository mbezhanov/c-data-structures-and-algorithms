CC=gcc
CFLAGS=-g3 -Wall

all: test

test: rbt_test.o rbt.o
	$(CC) $(CFLAGS) -o $@ $^
rbt_test.o: rbt_test.c rbt.h
rbt.o: rbt.c rbt.h

clean:
	$(RM) test *.o
