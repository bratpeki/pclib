#include "../lib/pbn.h"
#include "../lib/ptype.h"

void pBigNumPrint( pbn* bignum ) {

	psint i;

	if ( bignum == NULL ) {
		printf("Uninitialized.\n");
		return;
	}

	i = (bignum->dig).size - 1;

	if ( (bignum->dig).size == 0 ) {
		printf("0\n");
		return;
	}

	if ( bignum->negative ) printf("-");

	for ( ; i >= 0 ; i--)
		printf("%d", ((bignum->dig).data)[i]);
	printf("\n");

}

int main() {

	pbn a;
	pbn b;
	pbn* c = NULL;
	pbn_init(&a);
	pbn_init(&b);
	pbn_init(c);

	pbn_addN(&a, 106); /* 106 */
	pbn_addN(&a, 12); /* 118 */

	printf(
		"a addr: %p\nb addr: %p\nc addr: %p\n",
		(pvptr)&a,
		(pvptr)&b,
		(pvptr)c
	);

	pbn_addN(&b, 119); /* 119 */

	a.negative = P_TRUE; /* -118 */

	printf("%d\n", pbn_cmpN(a, 32) ); /* 6, the second arg is bigger */

	a.negative = P_FALSE; /* 118 */

	printf("%d\n", pbn_cmpN(a, 32));  /* 5 */
	printf("%d\n", pbn_cmpN(a, 117)); /* 5 */
	printf("%d\n", pbn_cmpN(a, 217)); /* 6 */
	printf("%d\n", pbn_cmpN(a, 118)); /* 7 */

	printf("%d\n", pbn_cmp(&a, &b)); /* 6 */

	printf("a: "); pBigNumPrint(&a);
	printf("b: "); pBigNumPrint(&b);
	printf("c: "); pBigNumPrint(c);

	c = pbn_add(&a, &b);
	if (c == NULL) return P_BADALLOC;

	printf("a: "); pBigNumPrint(&a);
	printf("b: "); pBigNumPrint(&b);
	printf("c: "); pBigNumPrint(c);

	pbn_clean(a);

	return P_SUCCESS;

}
