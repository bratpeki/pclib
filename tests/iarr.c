#include "../lib/piarr.h"
#include "../lib/pcode.h"
#include "../lib/ptype.h"

#include <stdio.h>

/* The user is responsible for checking the allocation successfulness */
#define addNCheck(arr, el) \
	piarr_add(arr, el); \
	if (arr.data == NULL) return P_BADALLOC;

int main() {

	int i;

	piarr(signed int) arrInt;
	piarr(signed short int) arrSrt;
	piarr_init(arrInt);
	piarr_init(arrSrt);

	addNCheck(arrInt, 1);
	addNCheck(arrInt, 2);
	addNCheck(arrInt, 3);

	addNCheck(arrSrt, 10);
	addNCheck(arrSrt, 20);
	addNCheck(arrSrt, 30);
	addNCheck(arrSrt, 40);
	addNCheck(arrSrt, 50);

	printf("Size of one signed int: %lu\n", sizeof(*arrInt.data));
	printf("Size of one signed short int: %lu\n", sizeof(*arrSrt.data));

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]); /* 1 2 3 */
	printf("(Size: %d)\n", arrInt.size); /* 3 */

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]); /* 10 20 30 40 50 */
	printf("(Size: %d)\n", arrSrt.size); /* 5 */

	piarr_rem(arrInt, 1); /* Removes 2 */
	piarr_rem(arrSrt, 0); /* Removes 10 */

	printf("arrInt size after removal: %d\n", arrInt.size); /* 2, contains 1 and 3 */
	printf("arrSrt size after removal: %d\n", arrSrt.size); /* 4, contains 20, 30, 40 and 50 */

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]); /* 1 3 */
	printf("\n");

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]); /* 20 30 40 50 */
	printf("\n");

	piarr_rem(arrInt, 0); printf("Size: %d\n", arrInt.size); /* Removed 1, size is 1 */
	piarr_rem(arrInt, 0); printf("Size: %d\n", arrInt.size); /* Removed 3, size is 0 */
	piarr_rem(arrInt, 0); printf("Size: %d\n", arrInt.size); /* Was empty, size is 0 */

	piarr_clean(arrInt);
	piarr_clean(arrSrt);

	return P_SUCCESS;

}
