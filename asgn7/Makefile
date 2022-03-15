cc = clang-format
CFLAGS = -Wall -Wextra -Wpedantic -g

.PHONY: all clean

all: identify

identify: bf.o bv.o node.o ht.o pq.o parser.o identify.o
	$(CC) bf.o bv.o bt.o node.o pq.o parser.o -o identify identify.o

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c -o node.o

ht.o: ht.c ht.h
	$(CC) $(CFLAGS) -c ht.c -o ht.o

pq.o: pq.c pq.h node.c node.h
	$(CC) $(CFLAGS) -c pq.c -o pq.o

bf.o: bf.c bf.h bv.c bv.h
	$(CC) $(CFLAGS) -c bf.c -o bf.o

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c -o bv.o

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c -o parser.o

speck.o: speck.h speck.c
	$(CC) $(CFLAGS) -c speck.c -o speck.o

text.o: text.h text.c
	$(CC) $(CFLAGS) -c text.c -o text.o


format:
	clang-format -i -style=file *[c,h]

clean:
	rm -f identify identify.o
	rm -f node.o ht.o pq.o bf.o bv.o parser.o speck.o text.o
