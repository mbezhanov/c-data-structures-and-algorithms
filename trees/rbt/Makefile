CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o rbt.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c utils.h rbt.h
rbt.o: rbt.c rbt.h
utils.o: utils.c utils.h

clean:
	$(RM) test *.o
