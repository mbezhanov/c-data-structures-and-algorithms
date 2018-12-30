CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o queue.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c queue.h utils.h
queue.o: queue.c queue.h
utils.o: utils.c utils.h

clean:
	$(RM) test *.o
