cc = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all clean

all: sorting

sorting: sorting.o batcher.o heap.o insert.o quick.o
        $(CC) sorting.o batcher.o heap.o insert.o quick.o   -o sorting

bathcher.o: batcher.c batcher.h
        $(CC) $(CFLAGS) -c batcher.c -o bathcer.o

heap.o: heap.c heap.h
        $(CC) $(CFLAGS) -c heap.c -o heap.o 

insert.o: insert.c insert.h
        $(CC) $(CFLAGS) -c insert.c -o insert.o

quick.o: quick.c quick.h
        $(CC) $(CFLAGS) -c quick.c  -o quick.o

clean:
        rm -f sorting sorting.o
