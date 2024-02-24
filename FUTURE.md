If adding features relating to C99, or switching to C99, it is important to note the following:
- C99 introduced the `long long` types for signed and unsigned integers
- C99 also introduced `stdint.h`, which has datatype of a standard size
- GCC compilation would be done using the `-std=c99` flag instead of `-ansi`
- Variadic macros would be useful for `pdbg_printf` (preprocessor implementation)

Consider preprocessor functions being capital snake case.
