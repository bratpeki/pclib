CC=gcc
FLAGS=-ansi -Wall -Wpedantic -Werror -g
OUT=$(shell find . -name '*.out')

all:
	$(CC) bignum.c -o bignum.out $(FLAGS)
	$(CC) bool.c -o bool.out $(FLAGS)
	$(CC) debug.c -o debug.out $(FLAGS)
	$(CC) dict.c -o dict.out $(FLAGS)
	$(CC) dynarr.c -o dynarr.out $(FLAGS)
	$(CC) idynarr.c -o idynarr.out $(FLAGS)

clean:
	rm $(OUT)
