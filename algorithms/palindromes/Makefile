CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o palindromes.o readline.o
	$(CC) $(CFLAGS) -o $@ $^
test.o: test.c palindromes.h
palindromes.o: palindromes.c palindromes.h
readline.o: readline.c readline.h
	$(CC) $(CFLAGS) -DREADLINE_PROMPT=\"Input\ a\ word:\" -c -o $@ $<

clean:
	$(RM) ./test *.o
