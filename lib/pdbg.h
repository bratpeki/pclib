#ifndef PCLIB_DBG
#define PCLIB_DBG

/*
 * pdebug.h
 *
 * Variables and functions for printf-ing debug messages
 */

#include "ptype.h"

#include <stdio.h>
#include <stdarg.h>

/*
 * The Boolean value which enables pdbg_printf output
 * True by default
 */
pbool _pdbg_toggle = P_ON;

/*
 * If debugging is enabled,
 * prints the given message to STDOUT, in printf's format
 */
void pdbg_printf(const char *format, ...) {

	if (_pdbg_toggle) {
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}

}

/* Set whether or not debug output is on */
#define pdbg_set(x) _pdbg_toggle = x

#endif
