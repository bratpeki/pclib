# PCLib - Peki's C Library

An ANSI C library aiming to implement modular, simple, fast and hackable tools for C/C++ programmers.

Each header file aims to be sufficiently documented and has minimal dependencies.

## The library

The entire library is, promptly, located in `lib`, with the structure detailed below:

- `ds`
  - `*tree`
  - `*stack`
  - `*ring`
  - `*llist1`
  - `*llist2`
- `etc`
  - `*dbg`
- `num`
  - `*complex`
  - `*bigint`
- `parse`
  - `*csv`
  - `*xml`
- `type`
  - `*bool`
  - `*str`
  
Items marked with `*` aren't implemented.

## Why ANSI C?

I chose ANSI C (C89, C90, ISO C, however you call it!) due to it being the very first C standard.
This, in turn, ensures that it is the most supported.

## Other documents

[`GUIDELINES.md`](./GUIDELINES.md) contains the guidelines to writing and compiling the PCLib code.

[`FUTURE.md`](./FUTURE.md) contains all notes relating to future revisions of PCLib.
