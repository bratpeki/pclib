#include "../lib/pbi.h"
#include "../lib/ptype.h"

#include <stdio.h>

#define test1(x) \
	printf("%d", pbi_isvalid(x))

pcode main() {

	/*
	 * pbi_isvalid
	 *
	 * Expected output:
	 * 11100110
	 */
	test1("0");
	test1("-0");
	test1("+0");
	test1("+");
	test1("-");
	test1("-248");
	test1("248");
	test1("24a8");
	printf("\n");

	return P_SUCCESS;

}
