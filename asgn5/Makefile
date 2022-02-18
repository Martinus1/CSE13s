cc = clang-format
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g
LFLAGS = $(shell pkg-config --libs gmp)

.PHONY: all clean

all: encrypt keygen decrypt

encrypt: encrypt.o numtheory.o randstate.o rsa.o
	$(CC) numtheory.o randstate.o rsa.o -o encrypt encrypt.o $(LFLAGS)

keygen: keygen.o numtheory.o randstate.o rsa.o
	$(CC) numtheory.o randstate.o rsa.o -o keygen keygen.o $(LFLAGS)

decrypt: decrypt.o numtheory.o randstate.o rsa.o
	$(CC) numtheory.o randstate.o rsa.o -o decrypt decrypt.o $(LFLAGS)

randstate.o: randstate.c randstate.h
	$(CC) $(CFLAGS) -c randstate.c -o randstate.o

numtheory.o: randstate.c randstate.h numtheory.c numtheory.h rsa.c
	$(CC) $(CFLAGS) -c numtheory.c randstate.c rsa.c -o numtheory.o

rsa.o: randstate.h numtheory.h rsa.h rsa.c
	$(CC) $(CFLAGS) -c rsa.c -o rsa.o

encrypt.o: randstate.h rsa.c numtheory.c numtheory.h
	$(CC) $(CFLAGS) -c encrypt.c numtheory.c

keygen.o: randstate.h rsa.h numtheory.h keygen.c
	$(CC) $(CFLAGS) -c keygen.c

decrypt.o:  randstate.h numtheory.c numtheory.h rsa.c rsa.h
	$(CC) $(CFLAGS) -c decrypt.c


format:
	clang-format -i -style=file *[c,h]

clean:
	rm -f decrypt decrypt.o
	rm -f encrypt encrypt.o
	rm -f keygen keygen.o
	rm -f randstate.o numtheory.o rsa.o
