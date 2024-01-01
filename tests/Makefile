CC=gcc
FLAGS=-ansi -Wall -Wpedantic -Werror
OUT=$(shell find . -name '*.out')

all:
	make bool debug

bool:
	$(CC) bool.c -o bool.out $(FLAGS)

debug:
	$(CC) debug.c -o debug.out $(FLAGS)

clean:
	rm $(OUT)

