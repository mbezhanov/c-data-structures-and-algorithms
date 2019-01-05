CC=gcc
CFLAGS=-g3 -Wall

all: test

test: test.o hash.o singly.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c hash.h singly.h
hash.o: hash.c hash.h singly.h
singly.o: singly.c singly.h

clean:
	$(RM) test *.o
