CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o lis.o utils.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c utils.h lis.h
lis.o: lis.c lis.h
utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -DDS_NAME=\"array\" -DDS_CONSTITUENTS_NAME=\"elements\" -c -o $@ $<

clean:
	$(RM) test *.o
