# PCLib - Peki's C Library

An ANSI C library aiming to implement modular, simple, fast and hackable tools for C/C++ programmers.

Each header file aims to be sufficiently documented and has minimal dependencies.

## Headers

| File | Description |
| - | - |
| `pcode.h` | Exit code macros |
| `pdarr.h` | Dynamic, type-generic array, efficient memory reallocation |
| `pdbg.h` | Functions for debug output |
| `pdict.h` | Dynamic, type-generic dictionary/hashmap |
| `pidarr.h` | Dynamic, type-generic array, incremental memory allocation |
| `ptype.h` | Custom datatypes |

## Why ANSI C?

I chose ANSI C (C89, C90, ISO C, however you call it!) due to it being the very first C standard.
This, in turn, ensures that it is the most supported.

## Other documents

[`FUTURE.md`](./FUTURE.md) contains all notes relating to future revisions of PCLib.

[`GUIDELINES.md`](./GUIDELINES.md) contains the guidelines to writing and compiling the PCLib code.
