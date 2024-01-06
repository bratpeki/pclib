CC=gcc
FLAGS=-ansi -Wall -Wpedantic -Werror
OUT=$(shell find . -name '*.out')

all:
	$(CC) bool.c -o bool.out $(FLAGS)
	$(CC) debug.c -o debug.out $(FLAGS)
	$(CC) dynarr.c -o dynarr.out $(FLAGS)

clean:
	rm $(OUT)

