cc = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all clean

all: integrate

integrate: integrate.o functions.o mathlib.o
	$(CC) functions.o integrate.o mathlib.o -o integrate

functions.o: functions.c functions.h 
	$(CC) $(CFLAGS) -c functions.c -o functions.o

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c -o integrate.o

mathlib.o: mathlib.c mathlib.h
	$(CC) $(CFLAGS) -c mathlib.c -o mathlib.o

clean:
	rm -f functions funtions.o
	rm -f integrate integrate.o

