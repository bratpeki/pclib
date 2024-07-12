#include <stdio.h>
#include <string.h>
#include "../lib/pbi.h"
#include "../lib/pcode.h"
#include "../lib/ptype.h"

pnoret bisplit( pbi* bi ) {

	psint len = strlen(bi), i;

	for ( i = len - 1; i >= 0; i-- ) {
		if ( ( i != len-1 ) && ( (len-i-1) % 3 == 0 ) ) printf(",");
		printf("%c", bi[len - i - 1]);
	}

}

int main() {

	pusint i;

	pbi a[100], b[100], c[100];
	memcpy(a, "0", 2);
	memcpy(b, "1", 2);

	/*
	 * To get the third number, we run the loop once ( 3 - 2 ).
	 * To get the forth, twice ( 4 - 2 ).
	 * By that logic, the 100th number is gotten after 98 runs.
	 */

	if ( _pbi_addb("5", "8", c, 100) == P_OUTOFBOUNDS ) return 10;

	for ( i = 0; i < 98; i++ ) {

		/*
		 * Although this if will never evaluate to true in this case,
		 * I added it to show an example of checking for error codes
		 */
		if ( pbi_add(a, b, c, 100) == P_OUTOFBOUNDS )
			return P_OUTOFBOUNDS;

		memcpy(a, b, 100);
		memcpy(b, c, 100);

	}

	printf("The 100th digit of the Fibbonaci sequence is ");
	bisplit(c);
	printf(".\n");

	return P_SUCCESS;

}
