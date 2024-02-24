Language:

- Write for ANSI C (C89/C90/ISO C)
- Fully use the standard library, only building upon it where deemed necessary
- A valid reason to reinvent the wheel is because you don't need the overhead of standard headers

Compiler:

- If using GCC, any tests or examples should be compiled using -ansi, -Wall, -Wpedantic and -Werror

Code:

- Don't write lines over 100 characters, unless deemed absolutely necessary
- The naming convention is as follows:

| Element | Description | Example |
| - | - | - |
| Single-line comment | Classic C-Style comment | `/* Example comment */` |
| Multi-line comment | | `/*` <br> ` * Example`  <br> ` * comment` <br> ` */` |
| Exit code | <!-- TODO: These are defined in pcodes.h --> | `P_EXITCODE` |
| Macro variable | | `P_MACROVAR` |
| Macro guard | | `PCLIB_GUARDNAME` |
| Function | | `pfile_desc()` |
| Macro function | Same as functions | `pfile_desc()` |
| Local variables | | `pfile_desc` |
| Type | | `p_typename` |
| Header | | `pfile.h`
| Test file | Same as headers, but without the `p`, and with the `.c` extension | `file.c` |
