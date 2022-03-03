cc = clang-format
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

.PHONY: all clean

all: encode decode

encode: io.h io.c huffman.h huffman.c
	$(CC) io.o huffman.o -o encode encode.o

decode: io.h io.c huffman.h huffman.c
	$(CC) io.o huffman.o -o encode decode.o

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c pq.h node.c node.h
	$(CC) $(CFLAGS) node.o -c pq.o

code.o: code.c code.h
	$(CC) $(CFLAGS) -c code.o

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.o

huffman.o: huffman.c huffman.h
	$(CC) $(CFLAGS) -c huffman.o



