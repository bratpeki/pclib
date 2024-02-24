# PCLib - Peki's C Library

An ANSI C library aiming to implement modular, simple, fast and hackable tools for C/C++ programmers.

Each header file aims to be sufficiently documented and has minimal dependencies.

## Headers

| File | Description | Include guard |
| - | - | - |
| `pcode.h` | Exit code macros | `PCLIB_CODE` |
| `pdarr.h` | Dynamic, type-generic array, efficient memory reallocation | `PCLIB_DARR` |
| `pdbg.h` | Functions for debug output | `PCLIB_DBG` |
| `pdict.h` | Dynamic, type-generic dictionary/hashmap | `PCLIB_DICT` |
| `pidarr.h` | Dynamic, type-generic array, incremental memory allocation | `PCLIB_IDARR` |
| `ptype.h` | Custom datatypes | `PCLIB_TYPE` |

## Why ANSI C?

I chose ANSI C (C89, C90, ISO C, however you call it!) due to it being the very first C standard.
This, in turn, ensures that it is the most supported.

## Other documents

[`FUTURE.md`](./FUTURE.md) contains all notes relating to future revisions of PCLib.

[`GUIDELINES.md`](./GUIDELINES.md) contains the guidelines to writing and compiling the PCLib code.
