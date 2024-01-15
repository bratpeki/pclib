
#include "../lib/pdynarr.h"
#include "../lib/ptypes.h"

#include <stdio.h>

int main() {

	int i;

	p_dynarr(p_sint) arrInt;
	p_dynarr(p_ssint) arrSrt;
	pDynArrInit(arrInt);
	pDynArrInit(arrSrt);

	pDynArrAdd(arrInt, 1);
	pDynArrAdd(arrInt, 2);
	pDynArrAdd(arrInt, 3);

	pDynArrAdd(arrSrt, 10);
	pDynArrAdd(arrSrt, 20);
	pDynArrAdd(arrSrt, 30);
	pDynArrAdd(arrSrt, 40);
	pDynArrAdd(arrSrt, 50);

	printf("%lu\n", sizeof(*arrInt.data));
	printf("%lu\n", sizeof(*arrSrt.data));

	for (i = 0; i < arrInt.size; i++)
		printf("%d (%u) ", (arrInt.data)[i], arrInt.cap);
	printf("\n");

	for (i = 0; i < arrSrt.size; i++)
		printf("%hd (%u) ", (arrSrt.data)[i], arrSrt.cap);
	printf("\n");

	pDynArrCleanup(arrInt);
	pDynArrCleanup(arrSrt);

	return 0;

}

