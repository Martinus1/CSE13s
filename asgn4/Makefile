cc = clang-format -i -style=file*.[c,h]
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

.PHONY: all clean

all: life

life: life.o universe.o
	$(CC) life.o universe.o -o life -lncurses

universe.o: universe.c universe.h
	$(CC) $(CFLAGS) -c universe.c -o universe.o

clean:
	rm -f life life.o
	rm -f universe.o
