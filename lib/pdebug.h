#ifndef PCLIB_DEBUG
#define PCLIB_DEBUG

/*
 * pdebug.h - Variables and functions for debug output
 *
 * "Debug output" refers to the output of debugging messages to STDOUT.
 */

#include "ptypes.h"

#include <stdio.h>

/*
 * The Boolean value which enables debug output
 * True by default
 */
p_bool pDebugToggle = p_on;

/* If debugging is enabled, print the debugging message to STDOUT */
#define pDebugPrintf(x) if(pDebugToggle)printf(x)

/* Set whether or not debug output is on */
#define pDebugSet(x) pDebugToggle = x

#endif
