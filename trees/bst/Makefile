CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o bst.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c utils.h bst.h
bst.o: bst.c bst.h
utils.o: utils.c utils.h

clean:
	$(RM) test *.o
