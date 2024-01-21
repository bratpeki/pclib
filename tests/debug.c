/*
 * debug.c - Testing the behaviour of the pdebug.h header file
 */

#include "../lib/pdebug.h"
#include "../lib/ptypes.h"

#define dmsg "DEBUG: "
#define emsg "ERROR: "

int main() {

	p_sint a = 2;

	/* Not actually necessary */
	pDebugSet(p_on);

	/* "DEBUG: Starting up..." */
	pDebugPrintf(dmsg "Starting up...\n");

	/* Nothing, since 'a' is 2 */
	if (a != 2) pDebugPrintf(emsg "'a' should have been 2, but is %d!\n", a);

	a = 3;

	/* "ERROR: 'a' should"... */
	if (a != 2) pDebugPrintf(emsg "'a' should have been 2, but is %d!\n", a);

	pDebugSet(p_off);

	/* Nothing, since the debug ouput is off */
	pDebugPrintf(dmsg "This won't print.\n");

	return 0;

}
