/*
 * limits.c - Testing limits.h
 */

#include "../lib/plimits.h"

#include <stdio.h>

int main() {

	pGetLimits();

	printf("pSCMax:  %d\n", pSCMax);
	printf("pSCMin: %d\n",  pSCMin);

	printf("pSIMax:  %d\n", pSIMax);
	printf("pSIMin: %d\n",  pSIMin);

	printf("pSLMax:  %ld\n", pSLMax);
	printf("pSLMin: %ld\n",  pSLMin);

	printf("pUCMax:  %u\n",  pUCMax);
	printf("pUIMax:  %u\n",  pUIMax);
	printf("pULMax:  %lu\n", pULMax);

	return 0;

}
