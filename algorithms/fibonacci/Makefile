CC=gcc
CFLAGS=-g3 -Wall

all: test_recursive test_iterative test_matrices

test_recursive: test.o recursive.o
	$(CC) $(CFLAGS) -o $@ $^
test_iterative: test.o iterative.o
	$(CC) $(CFLAGS) -o $@ $^
test_matrices: test.o matrices.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c fibonacci.h
recursive.o: recursive.c fibonacci.h
iterative.o: iterative.c fibonacci.h
matrices.o: matrices.c fibonacci.h

clean:
	$(RM) test_* *.o
