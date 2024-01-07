#ifndef PCLIB_LIMITS
#define PCLIB_LIMITS

/*
 * plimits.h - Finds the limits of the default datatypes,
 *             independent of the compiler or implementation
 *
 * This header usually isn't all that useful, due to the existence of limits.h,
 * but I've still created it, so that the limits can be compiled for any
 * ANSI C compiler running on any system capable of compiling ANSI C.
 *
 * It was also very fun to make!
 *
 * The following values are provided by the header, once pGetLimits is run:
 *
 * pSIntMax  - The maximum signed int
 * pSIntMin  - The minimum signed int
 *
 * pSLIntMax - The maximum signed long int
 * pSLIntMin - The minimum signed long int
 *
 * pUIntMax  - The maximum unsigned int
 * pULIntMin - The maximum unsigned long int
 */

#include "ptypes.h"

p_sint  pSIntMax,  pSIntMin;
p_slint pSLIntMax, pSLIntMin;

p_uint  pUIntMax;
p_ulint pULIntMax;

void pGetLimits() {

	p_sint  siMinusOne  = -1;
	p_slint sliMinusOne = -1;

	pUIntMax  = *(p_uint*)(&siMinusOne);
	pULIntMax = *(p_ulint*)(&sliMinusOne);

	pSIntMax  = pUIntMax/2;
	pSLIntMax = pULIntMax/2;

	pSIntMin  = -pSIntMax - 1;
	pSLIntMin = -pSLIntMax - 1;

}

#endif
