#include "../lib/pbi.h"
#include "../lib/ptype.h"
#include "../lib/pcode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BISIZE 20

pcode main() {

	pbi bi1[BISIZE] = "123324";
	pbi bi2[BISIZE] = "124";
	pbi bi3[BISIZE];

	_pbi_addb(bi1, bi2, bi3, BISIZE);
	printf("%s + %s = %s\n", bi1, bi2, bi3);

	_pbi_subb(bi1, bi2, bi3, BISIZE);
	printf("%s - %s = %s\n", bi1, bi2, bi3);

	memcpy(bi1, "1203", 5);
	memcpy(bi2, "0", 2);
	_pbi_subb(bi1, bi2, bi3, BISIZE);
	printf("%s - %s = %s\n", bi1, bi2, bi3);

	/* 1 1 1 1 */
	printf(
		"%d %d %d %d\n",
		pbi_cmp("0", "0", BISIZE) == P_EQUAL,
		pbi_cmp("10", "-10", BISIZE) == P_GREATER,
		pbi_cmp("-10", "-5", BISIZE) == P_SMALLER,
		pbi_cmp("10", "55", BISIZE) == P_SMALLER
	);

	/* TODO: Proper code checks */
	pbi_add("3", "-3", bi3, BISIZE);
	printf("3 + (-3) = %s\n", bi3);

	pbi_add("5", "-3", bi3, BISIZE);
	printf("5 + (-3) = %s\n", bi3);

	pbi_add("-5", "-3", bi3, BISIZE);
	printf("(-5) + (-3) = %s\n", bi3);

	pbi_add("5", "3434", bi3, BISIZE);
	printf("5 + 3434 = %s\n", bi3);

	pbi_add(bi3, bi1, bi2, BISIZE);
	printf("%s + %s = %s\n", bi3, bi1, bi2);

	_pbi_subb("0", "0", bi3, BISIZE);
	printf("0 - 0 = %s\n", bi3);

	pbi_sub("-100", "-100", bi3, BISIZE);
	printf("-100 - (-100) = %s\n", bi3);

	pbi_sub("-100", "100", bi3, BISIZE);
	printf("-100 - 100 = %s\n", bi3);

	pbi_sub("5", "3", bi3, BISIZE);
	printf("5 - 3 = %s\n", bi3);

	pbi_sub("3", "5", bi3, BISIZE);
	printf("3 - 5 = %s\n", bi3);

	return P_SUCCESS;

}
