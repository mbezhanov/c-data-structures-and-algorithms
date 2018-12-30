CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o avl.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c utils.h avl.h
avl.o: avl.c avl.h
utils.o: utils.c utils.h

clean:
	$(RM) test *.o
