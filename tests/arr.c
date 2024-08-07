#include "../lib/parr.h"
#include "../lib/pcode.h"
#include "../lib/ptype.h"

#include <stdio.h>

/* The user is responsible for checking the allocation successfulness */
#define addNCheck(arr, el) \
	parr_add(arr, el); \
	if (arr.data == NULL) return P_BADALLOC;

int main() {

	int i;

	parr(signed int) arrInt;
	parr(signed short int) arrSrt;
	parr_init(arrInt);
	parr_init(arrSrt);

	addNCheck(arrInt, 1);
	addNCheck(arrInt, 2);
	addNCheck(arrInt, 3);

	addNCheck(arrSrt, 10);
	addNCheck(arrSrt, 20);
	addNCheck(arrSrt, 30);
	addNCheck(arrSrt, 40);
	addNCheck(arrSrt, 50);
	addNCheck(arrSrt, 60);

	printf("Size of one signed int: %lu\n", sizeof(*arrInt.data));
	printf("Size of one signed short int: %lu\n", sizeof(*arrSrt.data));

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]); /* 1 2 3 */
	printf("(Capacity: %d)\n", arrInt.cap); /* The capaity doubles, so 4 */

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]); /* 10 20 30 40 50 60 */
	printf("(Capacity: %d)\n", arrSrt.cap); /* 8 */

	parr_rem(arrInt, 1); /* Removes 2 */
	parr_rem(arrSrt, 0); /* Removes 10 */

	printf("arrInt capacity after removal: %d\n", arrInt.cap); /* 2 */
	printf("arrSrt capacity after removal: %d\n", arrSrt.cap); /* 8 */

	printf("arrInt size after removal: %d\n", arrInt.size); /* 2, contains 1 and 3 */
	printf("arrSrt size after removal: %d\n", arrSrt.size); /* 5, contains 20, 30, 40, 50 and 60 */

	printf("arrInt: ");
	for (i = 0; i < arrInt.size; i++)
		printf("%d ", (arrInt.data)[i]); /* 1 3 */
	printf("\n");

	printf("arrSrt: ");
	for (i = 0; i < arrSrt.size; i++)
		printf("%hd ", (arrSrt.data)[i]); /* 20 30 40 50 60 */
	printf("\n");

	parr_rem(arrInt, 0);
	printf("Size: %d, Capacity: %d\n", arrInt.size, arrInt.cap); /* Removed 1, output is 1 and 1 */

	parr_rem(arrInt, 0);
	printf("Size: %d, Capacity: %d\n", arrInt.size, arrInt.cap); /* Removed 3, output is 0 and 0 */

	parr_rem(arrInt, 0);
	printf("Size: %d, Capacity: %d\n", arrInt.size, arrInt.cap); /* Was empty, output is 0 and 0 */

	parr_clean(arrInt);
	parr_clean(arrSrt);

	return P_SUCCESS;

}
