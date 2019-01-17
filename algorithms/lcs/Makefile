CC=gcc
CFLAGS=-g3 -Wall

all: test

test: test.o lcs.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c lcs.h
lcs.o: lcs.c lcs.h

clean:
	$(RM) test *.o
