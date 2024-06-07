If adding features relating to C99, or switching to C99, it is important to note the following:
- C99 introduced the `long long` types for signed and unsigned integers
- C99 also introduced `stdint.h`, which has datatype of a standard size
- GCC compilation would be done using the `-std=c99` flag instead of `-ansi`
- Variadic macros would be useful for `pdbg_printf` (preprocessor implementation)

I doubt I'll ever port this to C99, though.

Maybe I'll just use standard types, without my own typedefs, so that I don't create confusion.
If kept, the signed type would be standard, and the unsigned would a "u" added to them
(eg. psrt for a signed short int, and pusrt for an unsigned short int).
It is clearly visible how this creates confusion.

Function pointers are currently not supported in the dynamic arrays, due to their syntax.

Use `pstr` and `pchr*` to denote the difference between constant and array strings.
