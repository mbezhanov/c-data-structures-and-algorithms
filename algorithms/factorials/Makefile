CC=gcc
CFLAGS=-g3 -Wall

all: test_recursive test_iterative test_large

test_recursive: test.o factorial_recursive.o
	$(CC) $(CFLAGS) -o $@ $^
test_iterative: test.o factorial_iterative.o
	$(CC) $(CFLAGS) -o $@ $^
test_large: large.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c factorial.h
factorial_recursive.o: factorial.c factorial.h
	$(CC) $(CFLAGS) -D FACTORIAL_RECURSIVE -c -o $@ $<
factorial_iterative.o: factorial.c factorial.h
	$(CC) $(CFLAGS) -D FACTORIAL_ITERATIVE -c -o $@ $<

clean:
	$(RM) test_* *.o
