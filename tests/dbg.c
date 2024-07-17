#include "../lib/pdbg.h"
#include "../lib/ptype.h"

#define dmsg "DEBUG: "
#define emsg "ERROR: "

int main() {

	signed int a = 2;

	/* Not actually necessary */
	pdbg_set(P_ON);

	/* "DEBUG: Starting up..." */
	pdbg_printf(dmsg "Starting up...\n");

	/* Nothing, since 'a' is 2 */
	if (a != 2) pdbg_printf(emsg "'a' should have been 2, but is %d!\n", a);

	a = 3;

	/* "ERROR: 'a' should"... */
	if (a != 2) pdbg_printf(emsg "'a' should have been 2, but is %d!\n", a);

	pdbg_set(P_OFF);

	/* Nothing, since the debug ouput is off */
	pdbg_printf(dmsg "This won't print.\n");

	return 0;

}
