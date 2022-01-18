cc = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all

all: functions

functions: functions.o
	$(CC) -o functions.o

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c


clean:
	rm -f functions funtions.o

format:
	clang-format -i -style=file *.{c,h}
