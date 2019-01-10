CC=gcc
CFLAGS=-g3 -Wall

all: test

test: test.o palindromes.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c palindromes.h
palindromes.o: palindromes.c palindromes.h

clean:
	$(RM) ./test *.o
