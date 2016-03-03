CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -march=native

all: mehru.o
	$(CC) $(CFLAGS) -o mehru mehru.o $(LINKS)


clean: 
	rm mehru
	rm mehru.o