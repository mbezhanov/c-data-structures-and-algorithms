CC=gcc
CFLAGS=-g3 -Wall
INCLUDE_DIR=../utils
VPATH=$(INCLUDE_DIR)
CFLAGS+=$(addprefix -I ,$(INCLUDE_DIR))

all: test

test: test.o swap.o bubble.o selection.o insertion.o merge.o quick.o heap.o
	$(CC) $(CFLAGS) -o $@ $^

swap.o: swap.c swap.h
bubble.o: bubble/bubble.c bubble/bubble.h swap.h
selection.o: selection/selection.c selection/selection.h swap.h
insertion.o: insertion/insertion.c insertion/insertion.h
merge.o: merge/merge.c merge/merge.h
quick.o: quick/quick.c quick/quick.h swap.h
heap.o: heap/heap.c heap/heap.h swap.h

swap.o bubble.o selection.o insertion.o merge.o quick.o heap.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) ./test ./*.o
