#include "../lib/pbignum.h"

void pBigNumPrint( p_bignum bignum ) {

	p_sint i = bignum.dig.size - 1;

	for ( ; i >= 0 ; i--)
		printf("%d", ((bignum.dig).data)[i]);
	printf("\n");

}

int main() {

	p_bignum a;
	pBigNumInit(&a);

	pBigNumAddNum(&a, 17);

	pBigNumPrint(a);

	pBigNumCleanup(a);

	return 0;

}
