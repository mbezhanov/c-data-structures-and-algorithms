CC=gcc
CFLAGS=-g3 -Wall

all: test_iterative test_recursive

test_iterative: test.o splay_iterative.o ../utils/utils.o
	$(CC) $(CFLAGS) -o $@ $^
test_recursive: test.o splay_recursive.o ../utils/utils.o
	$(CC) $(CFLAGS) -D SPLAY_RECURSIVE -o $@ $^
test.o: test.c ../utils/utils.h splay.h
splay_iterative.o: splay.c splay.h
	$(CC) $(CFLAGS) -c -o $@ $<
splay_recursive.o: splay.c splay.h
	$(CC) $(CFLAGS) -D SPLAY_RECURSIVE -c -o $@ $<
../utils/utils.o: ../utils/utils.c ../utils/utils.h

clean:
	$(RM) ./test_iterative ./test_recursive *.o
