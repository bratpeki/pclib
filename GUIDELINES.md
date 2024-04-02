Language:

- Write for ANSI C (C89/C90)
- Fully use the standard library, only building upon it where deemed necessary
- A valid reason to reinvent the wheel is because you don't need the overhead of standard headers

Compiler:

- If using GCC, any tests or examples should be compiled using `-ansi -Wall -Wpedantic -Werror`

Code:

- Don't write lines over 100 characters, unless deemed absolutely necessary
- The naming convention is as follows:

<!-- TODO: Ifs, function brackets -->
| Element | Example | Description |
| - | - | - |
| Single-line comment | `/* Example comment */` | Classic C-Style comment |
| Multi-line comment | `/*` <br> ` * Example`  <br> ` * comment` <br> ` */` | |
| Enumerator values | `P_ENUMVALUE` | Used for exit codes and Boolean values |
| Macro variable | `P_MACROVAR` | |
| Macro guard | `PCLIB_FILE` | |
| Function | `pfile_desc()` | |
| Macro function | `pfile_desc()` | Same as functions |
| Local variables | `pfile_desc` | |
| Type | `ptypename` | |
| Header | `pfile.h` | |
| Test file | `file.c` | |

<!-- TODO: Make this more apparent! -->
Any element that __shouldn't be accessed by the user__ is prefixed with a `_`.
