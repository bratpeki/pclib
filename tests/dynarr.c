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

	printf("Size of one p_sint: %lu\n", sizeof(*arrInt.data));
	printf("Size of one p_ssint: %lu\n", sizeof(*arrSrt.data));

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]);
	printf("\n");

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]);
	printf("\n");

	pDynArrRemove(arrInt, 1); /* Removes 2 */
	pDynArrRemove(arrSrt, 0); /* Removes 10 */

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
