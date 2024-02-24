CC=gcc
FLAGS=-ansi -Wall -Wpedantic -Werror -g
OUT=$(shell find . -name '*.out')

all:
	#$(CC) bn.c    -o bnm.out $(FLAGS)
	$(CC) bool.c  -o bool.out $(FLAGS)
	$(CC) dbg.c   -o dbg.out $(FLAGS)
	$(CC) dict.c  -o dict.out $(FLAGS)
	$(CC) darr.c  -o darr.out $(FLAGS)
	$(CC) idarr.c -o idarr.out $(FLAGS)

clean:
	rm $(OUT)
