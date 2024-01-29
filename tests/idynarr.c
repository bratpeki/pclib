#include "../lib/pidynarr.h"
#include "../lib/pcodes.h"
#include "../lib/ptypes.h"

#include <stdio.h>

/* The user is responsible for checking the allocation successfulness */

#define arrAddAndCheck(arr, el) \
	pIDynArrAdd(arr, el); \
	if (arr.data == NULL) return P_BADALLOC;

int main() {

	int i;

	p_idynarr(p_sint) arrInt;
	p_idynarr(p_ssint) arrSrt;
	pIDynArrInit(arrInt);
	pIDynArrInit(arrSrt);

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
		printf("%d ", (arrInt.data)[i]); /* 1 2 3 */
	printf(" (Size: %d)\n", arrInt.size); /* 3 */

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]); /* 10 20 30 40 50 */
	printf(" (Size: %d)\n", arrSrt.size); /* 5 */

	pIDynArrRemove(arrInt, 1); /* Removes 2 */
	pIDynArrRemove(arrSrt, 0); /* Removes 10 */

	printf("arrInt size after removal: %d\n", arrInt.size); /* 2, contains 1 and 3 */
	printf("arrSrt size after removal: %d\n", arrSrt.size); /* 4, contains 20, 30, 40 and 50 */

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]);
	printf("\n");

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]);
	printf("\n");

	/* Let's test what happens when an array is emptied */

	pIDynArrRemove(arrInt, 0); printf("Size: %d\n", arrInt.size); /* Removed 1, size is 1 */
	pIDynArrRemove(arrInt, 0); printf("Size: %d\n", arrInt.size); /* Removed 3, size is 0 */
	pIDynArrRemove(arrInt, 0); printf("Size: %d\n", arrInt.size); /* Was empty, size is 0 */

	pIDynArrCleanup(arrInt);
	pIDynArrCleanup(arrSrt);

	return P_SUCCESS;

}
