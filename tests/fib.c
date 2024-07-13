#include "../lib/pbi.h"
#include "../lib/pcode.h"
#include "../lib/ptype.h"

#include <stdio.h>
#include <string.h>

#define N 1000 /* Must be greater than 2 */
#define BISIZE 250 /* Must be greater than or equal to 2 */

pnoret bisplit( pbi* bi ) {
	psint len = strlen(bi), i;
	for ( i = 0; i < len; i++ ) {
		if ( (i != 0) && (len-i) % 3 == 0 ) printf(",");
		printf("%c", bi[i]);
	}
}

int main() {

	pusint i;

	pbi a[BISIZE], b[BISIZE], c[BISIZE];
	memcpy(a, "0", 2);
	memcpy(b, "1", 2);

	/*
	 * To get the third number, we run the loop once ( 3 - 2 ),
	 * to get the forth, twice ( 4 - 2 ),
	 * etc.
	 */

	for ( i = 0; i < N - 2; i++ ) {

		/*
		 * Although this if will never evaluate to true in this case,
		 * I added it to show an example of checking for error codes
		 */
		if ( pbi_add(a, b, c, BISIZE) == P_OUTOFBOUNDS ) {
			printf("Error on iteration with index %hu, try making the bignum larger\n", i);
			return P_OUTOFBOUNDS;
		}

		memcpy(a, b, BISIZE);
		memcpy(b, c, BISIZE);

	}

	printf("Number %d of the Fibbonaci sequence is ", N);
	bisplit(c);
	printf(".\n");

	return P_SUCCESS;

}
