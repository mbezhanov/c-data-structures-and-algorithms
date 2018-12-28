CC=gcc
CFLAGS=-g3 -Wall

all: test

test: test.o treap.o ../utils/utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c ../utils/utils.h treap.h
treap.o: treap.c treap.h
../utils/utils.o: ../utils/utils.c ../utils/utils.h

clean:
	$(RM) test *.o
