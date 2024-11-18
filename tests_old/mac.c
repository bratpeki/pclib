#include "../lib/pmac.h"
#include "../lib/pcode.h"

#include <stdio.h>

pcode main() {

	float interpolate = PMAC_LININT(0, -10, 1, 100, 0.3);
	printf( "%f\n", interpolate );

	return P_SUCCESS;

}
