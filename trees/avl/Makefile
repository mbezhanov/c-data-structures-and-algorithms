CC=gcc
CFLAGS=-g3 -Wall

all: test

test: test.o avl.o ../utils/utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c ../utils/utils.h avl.h
avl.o: avl.c avl.h
../utils/utils.o: ../utils/utils.c ../utils/utils.h

clean:
	$(RM) test *.o
