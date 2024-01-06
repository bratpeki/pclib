
/*
 * debug.c - Testing the behaviour of the pdebug.h header file
 */

#include "../lib/pdebug.h"
#include "../lib/ptypes.h"

#define dmsg "DEBUG: "
#define emsg "ERROR: "

int main() {

	p_sbyte a = 2;

	/* Not actually necessary */
	pDebugSet(p_on);

	/* "DEBUG: Starting up..." */
	pDebugPrintf(dmsg "Starting up...\n");

	/* Nothing */
	if (a != 2) pDebugPrintf(emsg "The expected value of 'a' was 2!\n");

	a = 3;

	/* "ERROR: The expected"... */
	if (a != 2) pDebugPrintf(emsg "The expected value of 'a' was 2!\n");

	pDebugSet(p_off);

	/* Nothing */
	pDebugPrintf(dmsg "This won't print.\n");

	return 0;

}

