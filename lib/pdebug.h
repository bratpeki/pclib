#ifndef PCLIB_DEBUG
#define PCLIB_DEBUG

/*
 * pdebug.h
 *
 * Variables and functions for printf-ing debug messages
 */

#include "ptypes.h"

#include <stdio.h>
#include <stdarg.h>

/*
 * The Boolean value which enables pDebugPrintf output
 * True by default
 */
p_bool pDebugToggle = p_on;

/*
 * If debugging is enabled,
 * prints the given message to STDOUT, in printf's format
 */
void pDebugPrintf(const char *format, ...) {

	if (pDebugToggle) {
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
	}

}

/* Set whether or not debug output is on */
#define pDebugSet(x) pDebugToggle = x

#endif
