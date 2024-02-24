/*
 * debug.c - Testing the behaviour of the pdebug.h header file
 */

#include "../lib/pdbg.h"
#include "../lib/ptype.h"

#define dmsg "DEBUG: "
#define emsg "ERROR: "

int main() {

	p_sint a = 2;

	/* Not actually necessary */
	pdbg_set(p_on);

	/* "DEBUG: Starting up..." */
	pdbg_printf(dmsg "Starting up...\n");

	/* Nothing, since 'a' is 2 */
	if (a != 2) pdbg_printf(emsg "'a' should have been 2, but is %d!\n", a);

	a = 3;

	/* "ERROR: 'a' should"... */
	if (a != 2) pdbg_printf(emsg "'a' should have been 2, but is %d!\n", a);

	pdbg_set(p_off);

	/* Nothing, since the debug ouput is off */
	pdbg_printf(dmsg "This won't print.\n");

	return 0;

}
