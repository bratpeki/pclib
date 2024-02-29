#include "../lib/pbi.h"
#include "../lib/ptype.h"

#include <stdio.h>

#define test1(x) printf("%d", pbi_isval(x))
#define test2(x) printf("%d", pbi_isneg(x))
#define test3(x, y) printf("%d", pbi_cmp(x, y) )
#define test4(x, y) printf("%d", pbi_cmpN(x, y) )

pcode main() {

	pbi b1 = "123";
	pbi b2 = "945";
	pbi b3 = "1945";
	pbi bNULL;

	pbi b12; /* b1 + b2 */
	pbi b112; /* b1 + (b1 + b2) */
	pbi b13; /* b1 + b3 */

	/*
	 * pbi_isvalid
	 *
	 * Expected output:
	 * 100110
	 */
	test1("0");
	test1("-0");
	test1("-");
	test1("-248");
	test1("248");
	test1("24a8");
	printf("\n");

	/* Expect all ones */
	test1(b1);
	test1(b2);
	test1(b3);
	printf("\n");

	/*
	 * pbi_isneg
	 *
	 * Expected output:
	 * 0100
	 */
	test2("0");
	test2("-248");
	test2("248");
	test2("2458");
	printf("\n");

	/*
	 * pbi_cmp
	 * Expected output:
	 * 5657
	 */

	test3("482", "17");
	test3("48",  "172");
	test3("173", "172");
	test3("172", "172");
	printf("\n");

	/*
	 * pbi_cmpN
	 * Expected output:
	 * 5657
	 */

	test4("482", 17);
	test4("48",  172);
	test4("173", 172);
	test4("172", 172);
	printf("\n");

	/* pbi_add testing */

	b12 = pbi_add(b1, b2);
	if ( b12 == NULL ) return P_BADALLOC;
	printf("%s + %s = %s\n", b1, b2, b12);

	b112 = pbi_add(b1, b12);
	if ( b112 == NULL ) { free(b12); return P_BADALLOC; }
	printf("%s + %s = %s\n", b1, b12, b112);

	b13 = pbi_add(b1, b3);
	if ( b13 == NULL ) { free(b12); free(b112); return P_BADALLOC; }
	printf("%s + %s = %s\n", b1, b3, b13);

	bNULL = pbi_add(b1, "0");
	if ( bNULL == NULL ) { free(b12); free(b112); free(b13); return P_BADALLOC; }
	printf( "%s + 0 = %s\n", b1, bNULL );

	free(b12);
	free(b112);
	free(b13);
	free(bNULL);

	/* pbi_sub testing */

	b12 = pbi_sub(b2, "800");
	if (b12 == NULL) return P_BADALLOC;
	printf("%s - 800 = %s\n", b2, b12);
	free(b12);

	b12 = pbi_sub(b2, "900");
	if (b12 == NULL) return P_BADALLOC;
	printf("%s - 900 = %s\n", b2, b12);
	free(b12);

	b12 = pbi_sub(b2, "156");
	if (b12 == NULL) return P_BADALLOC;
	printf("%s - 156 = %s\n", b2, b12);
	free(b12);

	return P_SUCCESS;

}
