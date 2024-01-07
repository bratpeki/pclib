/*
 * limits.c - Testing limits.h
 */

#include "../lib/plimits.h"

#include <stdio.h>

int main() {

	pGetLimits();

	printf(
		"pUIntMax:   %u\n"
		"pULIntMax:  %lu\n"
		"pSIntMax:   %d\n"
		"pSIntMin:  %d\n"
		"pSLIntMax:  %ld\n"
		"pSLIntMin: %ld\n"
		,
		pUIntMax,
		pULIntMax,
		pSIntMax,
		pSIntMin,
		pSLIntMax,
		pSLIntMin
	);

	return 0;

}
