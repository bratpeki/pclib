If adding features relating to C99, or switching to C99, it is important to note the following:
- C99 introduced the `long long` types for signed and unsigned integers
- C99 also introduced `stdint.h`, which has datatype of a standard size
- GCC compilation would be done using the `-std=c99` flag instead of `-ansi`
- Variadic macros would be useful for `pdbg_printf` (preprocessor implementation)

I doubt I'll ever port this to C99, though.

Function pointers are currently not supported in the dynamic arrays, due to their syntax.

---

- Encryption
- Hashing
- Regular expressions