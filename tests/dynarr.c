
#include "../lib/pdynarr.h"
#include "../lib/ptypes.h"

int main() {

	p_dynarr(p_sint) arrInt;
	p_dynarr(p_ssint) arrSrt;
	pDynArrInit(arrInt);
	pDynArrInit(arrSrt);

	printf("%lu\n", sizeof(*arrInt.data));
	printf("%lu\n", sizeof(*arrSrt.data));

	pDynArrCleanup(arrInt);
	pDynArrCleanup(arrSrt);

	return 0;

}

