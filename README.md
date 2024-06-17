# PCLib - Peki's C Library

An ANSI C library aiming to implement modular, simple, fast and hackable tools for C/C++ programmers.

Each header file aims to be sufficiently documented and has minimal dependencies.

## Headers

| File | Description |
| - | - |
| `ptype.h` | Custom datatypes |
| `pcode.h` | Exit code macros |
| `pdbg.h` | Functions for debug output |
| `parr.h` | Dynamic, type-generic array, with efficient memory reallocation |
| `piarr.h` | Dynamic, type-generic array, with incremental memory allocation |
| `pdict.h` | Dynamic, type-generic dictionary/hashmap |
| `pstr.h` | Various string functions |
| `pmac.h` | Useful macros |

## Why ANSI C?

I chose ANSI C (C89, C90, ISO C, however you call it!) due to it being the very first C standard.
This, in turn, ensures that it is the most supported.

## Other documents

[`GUIDELINES.md`](./GUIDELINES.md) contains the guidelines to writing and compiling the PCLib code.

[`FUTURE.md`](./FUTURE.md) contains all notes relating to future revisions of PCLib.
