CC=gcc
CFLAGS=-g3 -Wall

all: test

test: test.o rbt.o ../utils/utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c ../utils/utils.h rbt.h
rbt.o: rbt.c rbt.h
../utils/utils.o: ../utils/utils.c ../utils/utils.h

clean:
	$(RM) test *.o
