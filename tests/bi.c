#include "../lib/pbi.h"
#include "../lib/ptype.h"
#include "../lib/pcode.h"

#include <stdio.h>
#include <string.h>

#define test1(x, y, z) printf("%d", z(x) == y)
#define test2(x, y, z, j) printf( "%d", z(x,y) == j )
#define test3(x, y) printf("%d", strcmp(x, y) == 0 )
/* TODO: Consider re-adding this */
/* #define test4(x, y) printf("%d", pbi_cmpN(x, y) ) */

pcode main() {

	pbi b1 = "123";
	pbi b2 = "945";
	pbi b3 = "1945";

	/* Stores the results of our calculations */
	pbi br1;
	pbi br2;
	pbi br3;

	/* pbi_isvalid */

	test1("0", 1, pbi_isval);
	test1("-0", 0, pbi_isval);
	test1("-", 0, pbi_isval);
	test1("-248", 1, pbi_isval);
	test1("248", 1, pbi_isval);
	test1("24a8", 0, pbi_isval);
	printf("\n");

	test1(b1, 1, pbi_isval);
	test1(b2, 1, pbi_isval);
	test1(b3, 1, pbi_isval);
	printf("\n");

	/* pbi_isneg */

	test1("0", 0, pbi_isneg);
	test1("-248", 1, pbi_isneg);
	test1("248", 0, pbi_isneg);
	test1("2458", 0, pbi_isneg);
	printf("\n");

	/* pbi_cmp */

	test2("482", "17", pbi_cmp, P_GREATER);
	test2("48",  "172", pbi_cmp, P_SMALLER);
	test2("173", "172", pbi_cmp, P_GREATER);
	test2("172", "172", pbi_cmp, P_EQUAL);
	printf("\n");

	/* _pbi_addb testing */

	br1 = _pbi_addb(b1, b2);
	br2 = _pbi_addb(b1, br1);
	br3 = _pbi_addb(b1, b3);

	if (
		( br1 == NULL ) ||
		( br2 == NULL ) ||
		( br3 == NULL )
	) {
		printf("_pbi_addb: Not enough memory.\n");
		return P_BADALLOC;
	}

	test3(br1, "1068");
	test3(br2, "1191");
	test3(br3, "2068");
	printf("\n");

	free(br1);
	free(br2);
	free(br3);

	/* _pbi_subb testing */

	br1 = _pbi_subb(b2, b1);
	br2 = _pbi_subb(b3, b1);
	br3 = _pbi_subb(b3, b2);

	if (
		( br1 == NULL ) ||
		( br2 == NULL ) ||
		( br3 == NULL )
	) {
		printf("_pbi_subb: Not enough memory.\n");
		return P_BADALLOC;
	}

	test3(br1, "822");
	test3(br2, "1822");
	test3(br3, "1000");
	printf("\n");

	free(br1);
	free(br2);
	free(br3);

	return P_SUCCESS;

}
