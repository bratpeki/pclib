#include "../lib/pdynarr.h"
#include "../lib/pcodes.h"
#include "../lib/ptypes.h"

#include <stdio.h>

/* The user is responsible for checking the allocation successfulness */

#define arrAddAndCheck(arr, el) \
	pDynArrAdd(arr, el); \
	if (arr.data == NULL) return P_BADALLOC;

int main() {

	int i;

	p_dynarr(p_sint) arrInt;
	p_dynarr(p_ssint) arrSrt;
	pDynArrInit(arrInt);
	pDynArrInit(arrSrt);

	arrAddAndCheck(arrInt, 1);
	arrAddAndCheck(arrInt, 2);
	arrAddAndCheck(arrInt, 3);

	arrAddAndCheck(arrSrt, 10);
	arrAddAndCheck(arrSrt, 20);
	arrAddAndCheck(arrSrt, 30);
	arrAddAndCheck(arrSrt, 40);
	arrAddAndCheck(arrSrt, 50);
	arrAddAndCheck(arrSrt, 60);

	printf("Size of one p_sint: %lu\n", sizeof(*arrInt.data));
	printf("Size of one p_ssint: %lu\n", sizeof(*arrSrt.data));

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]); /* 1 2 3 */
	printf(" (Capacity: %d)\n", arrInt.cap); /* The capaity doubles, so 4 */

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]); /* 10 20 30 40 50 60 */
	printf(" (Capacity: %d)\n", arrSrt.cap); /* 8 */

	pDynArrRemove(arrInt, 1); /* Removes 2 */
	pDynArrRemove(arrSrt, 0); /* Removes 10 */

	printf("arrInt capacity after removal: %d\n", arrInt.cap); /* 2 */
	printf("arrSrt capacity after removal: %d\n", arrSrt.cap); /* 8 */

	printf("arrInt size after removal: %d\n", arrInt.size); /* 2, contains 1 and 3 */
	printf("arrSrt size after removal: %d\n", arrSrt.size); /* 5, contains 20, 30, 40, 50 and 60 */

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]);
	printf("\n");

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]);
	printf("\n");

	pDynArrCleanup(arrInt);
	pDynArrCleanup(arrSrt);

	return P_SUCCESS;

}
