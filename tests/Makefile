CC=gcc
FLAGS=-ansi -Wall -Wpedantic -Werror -g
OUT=$(shell find . -name '*.out')

build:
	$(CC) bn.c   -o bn.out $(FLAGS)
	$(CC) bool.c -o bool.out $(FLAGS)
	$(CC) dbg.c  -o dbg.out $(FLAGS)
	$(CC) dict.c -o dict.out $(FLAGS)
	$(CC) arr.c  -o arr.out $(FLAGS)
	$(CC) iarr.c -o iarr.out $(FLAGS)

clean:
	rm $(OUT)
