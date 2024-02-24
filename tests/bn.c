#include "../lib/pbn.h"
#include "../lib/ptype.h"

void pBigNumPrint( pbn bignum ) {

	psint i = bignum.dig.size - 1;

	if ( (bignum.dig).size == 0 ) return;

	if ( bignum.negative ) printf("-");

	for ( ; i >= 0 ; i--)
		printf("%d", ((bignum.dig).data)[i]);
	printf("\n");

}

int main() {

	pbn a;
	pbn_init(&a);

	pbn_addN(&a, 106); /* 106 */
	pbn_addN(&a, 12); /* 118 */

	a.negative = P_TRUE; /* -118 */

	printf("%d\n", pbn_cmpN(a, 32) ); /* 6, the second arg is bigger */

	a.negative = P_FALSE; /* 118 */

	printf("%d\n", pbn_cmpN(a, 32)); /* 5 */
	printf("%d\n", pbn_cmpN(a, 117)); /* 5 */

	/* pBigNumPrint(a); */

	pbn_clean(a);

	return 0;

}
