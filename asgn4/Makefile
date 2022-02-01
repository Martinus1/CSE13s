cc = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

.PHONY: all clean

all: life

life: life.o universe.o
	$(CC) life.o universe.o -o life

universe.o: universe.c universe.h
	$(CC) $(CFLAGS) -c universe.c -o universe.o

clean:
	rm -f life life.o

