cc = clang-format
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

.PHONY: all clean

all: encode decode

encode: io.o huffman.o node.o pq.o code.o
	$(CC) io.o huffman.o node.o pq.o code.o -o encode encode.o

decode: io.o huffman.o node.o pq.o code.o
	$(CC) io.o huffman.o node.o pq.o code.o -o decode decode.o

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c pq.h node.c node.h
	$(CC) $(CFLAGS) node.o pq.o -c pq.o

code.o: code.c code.h
	$(CC) $(CFLAGS) -c code.o

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o

huffman.o: huffman.c huffman.h 
	$(CC) $(CFLAGS) -c huffman.c -o huffman.o

encode.o: node.h pq.h code.h io.h huffman.h
	$(CC) $(CFLAGS) -c encode.c

decode.o: node.h pq.h code.h io.h huffman.h
	$(CC) $(CFLAGS) -c decode.c


format:
	clang-format -i -style=file *[c,h]

clean:
	rm -f encode encode.o decode decode.o
	rm -f node.o pq.o code.o io.o huffman.o

