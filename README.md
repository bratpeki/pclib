# PCLib - Peki's C Library

An ANSI C library aiming to implement modular, simple, fast and hackable tools for C/C++ programmers.

Each header file aims to be sufficiently documented and has minimal dependencies.

## Headers

| File | Description | Include guard |
| - | - | - |
| `ptypes.h` | Custom datatypes | `PCLIB_TYPES` |
| `pcodes.h` | Exit code macros | `PCLIB_CODES` |
| `pdebug.h` | Functions for debug output | `PCLIB_DEBUG` |
| `pdynarr.h` | Dynamic, type-generic array, efficient memory reallocation | `PCLIB_DYNARR` |
| `pidynarr.h` | Dynamic, type-generic array, incremental memory allocation | `PCLIB_IDYNARR` |
| `pdict.h` | Dynamic, type-generic dictionary/hashmap | `PCLIB_DICT` |

## Why ANSI C?

I chose ANSI C (C89, C90, ISO C, however you call it!) due to it being the very first C standard.
This, in turn, ensures that it is the most supported.
