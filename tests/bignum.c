#include "../lib/pbignum.h"
#include "../lib/ptypes.h"

void pBigNumPrint( p_bignum bignum ) {

	p_sint i = bignum.dig.size - 1;

	if ( (bignum.dig).size == 0 ) return;

	if ( bignum.negative ) printf("-");

	for ( ; i >= 0 ; i--)
		printf("%d", ((bignum.dig).data)[i]);
	printf("\n");

}

int main() {

	p_bignum a;
	pBigNumInit(&a);

	pBigNumAddNum(&a, 106); /* 106 */
	pBigNumAddNum(&a, 12); /* 118 */

	a.negative = p_true; /* -118 */

	printf("%d\n", pBigNumCompNum(a, 32) ); /* 6, the second arg is bigger */

	a.negative = p_false; /* 118 */

	printf("%d\n", pBigNumCompNum(a, 32)); /* 5 */
	printf("%d\n", pBigNumCompNum(a, 117)); /* 5 */

	/* pBigNumPrint(a); */

	pBigNumCleanup(a);

	return 0;

}
