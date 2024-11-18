CC=gcc
CFLAGS=-ansi -Wall -Wpedantic -Werror -g
SRCS=$(wildcard *.c)
BINS=$(SRCS:.c=.out)

.PHONY: all clean

all: $(BINS)

%.out: %.c
	$(CC) $< -o $@ $(CFLAGS)

clean:
	rm -f $(BINS) core*
