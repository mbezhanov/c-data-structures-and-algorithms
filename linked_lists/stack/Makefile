CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o stack.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c stack.h utils.h
stack.o: stack.c stack.h
utils.o: utils.c utils.h

clean:
	$(RM) test *.o
