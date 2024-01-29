#include "../lib/pbignum.h"

int main() {

	p_bignum a;
	pBigNumInit(&a);

	pBigNumAddNum(&a, 17);

	return 0;

}
