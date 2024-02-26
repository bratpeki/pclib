#include "../lib/pbn.h"
#include "../lib/ptype.h"

void pBigNumPrint( pbn* bignum ) {

	psint i;

	if ( bignum == NULL ) {
		printf("Uninitialized.\n");
		return;
	}

	i = (bignum->dig).size - 1;

	if (pbn_isnull(bignum) ) { printf("0\n"); return; }

	if ( bignum->negative ) printf("-");

	for ( ; i >= 0 ; i--)
		printf("%d", ((bignum->dig).data)[i]);
	printf("\n");

}

int main() {

	pbn* bn1;
	pbn* bn2;

	pbn_init(&bn1);
	printf("%d\n", pbn_isnull(bn1)); /* 1, because any initialized bignum is set to 0 */
	pBigNumPrint(bn1); /* 0, for the reason stated above */

	pbn_addN(bn1, 100); pBigNumPrint(bn1);
	pbn_addN(bn1, 10); pBigNumPrint(bn1);
	pbn_addN(bn1, 1); pBigNumPrint(bn1);

	/* TODO: Consider the negative context */

	bn2 = pbn_add(bn1, bn1);

	pBigNumPrint(bn2);

	return P_SUCCESS;

}
