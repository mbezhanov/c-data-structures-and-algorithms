CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o deque.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c deque.h utils.h
deque.o: deque.c deque.h
utils.o: utils.c utils.h

clean:
	$(RM) test *.o
