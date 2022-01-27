cc = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

.PHONY: all clean

all: sorting

sorting: sorting.o batcher.o heap.o insert.o quick.o stats.o
	$(CC) sorting.o batcher.o heap.o insert.o quick.o stats.o -o sorting

bathcher.o: batcher.c batcher.h stats.h
	$(CC) $(CFLAGS) -c batcher.c -o bathcher.o

heap.o: heap.c heap.h stats.h
	$(CC) $(CFLAGS) -c heap.c -o heap.o 

insert.o: insert.c insert.h stats.h
	$(CC) $(CFLAGS) -c insert.c -o insert.o

quick.o: quick.c quick.h stats.h
	$(CC) $(CFLAGS) -c quick.c -o quick.o

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c -o stats.o

clean:
	rm -f sorting sorting.o
