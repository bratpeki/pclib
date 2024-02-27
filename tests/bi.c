#include "../lib/pbi.h"
#include "../lib/ptype.h"

#include <stdio.h>

#define test1(x) printf("%d", pbi_isvalid(x))
#define test2(x) printf("%d", pbi_isneg(x))
#define test3(x, y) printf("%d", pbi_cmp(x, y) )
#define test4(x, y) printf("%d", pbi_cmpN(x, y) )

pcode main() {

	pbi b1 = "123";
	pbi b2 = "45"; /* TODO: Not right when 945 */
	pbi b12; /* 1 + 2 */
	pbi b112; /* 1 + (1 + 2) */

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

	b12 = pbi_add(b1, b2);
	printf("%s + %s = %s\n", b1, b2, b12);
	b12 = pbi_add(b1, b2);
	printf("%s + %s = %s\n", b1, b2, b12);
	b112 = pbi_add(b1, b12);
	printf("%s + %s = %s\n", b1, b12, b112);

	free(b12);
	free(b112);

	return P_SUCCESS;

}
