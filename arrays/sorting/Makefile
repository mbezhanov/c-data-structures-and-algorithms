CC=gcc
CFLAGS=-g3 -Wall

all: test

test: test.o swap.o bubble.o selection.o insertion.o merge.o quick.o heap.o
	$(CC) $(CFLAGS) -o $@ $^

swap.o: utils/swap.c utils/swap.h
bubble.o: bubble/bubble.c bubble/bubble.h utils/swap.h
selection.o: selection/selection.c selection/selection.h utils/swap.h
insertion.o: insertion/insertion.c insertion/insertion.h
merge.o: merge/merge.c merge/merge.h
quick.o: quick/quick.c quick/quick.h utils/swap.h
heap.o: heap/heap.c heap/heap.h utils/swap.h

swap.o bubble.o selection.o insertion.o merge.o quick.o heap.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) ./test ./*.o
