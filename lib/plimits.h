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
 * pSCMax - The maximum signed character
 * pSCMin - The minimum signed character
 *
 * pSIMax - The maximum signed int
 * pSIMin - The minimum signed int
 *
 * pSLMax - The maximum signed long int
 * pSLMin - The minimum signed long int
 *
 * pUCMax - The maximum unsigned character
 * pUIMax - The maximum unsigned int
 * pULMax - The maximum unsigned long
 */

#include "ptypes.h"

p_sint  pSIMax, pSIMin; p_uint  pUIMax;
p_slint pSLMax, pSLMin; p_ulint pULMax;
p_schr  pSCMax, pSCMin; p_uchr  pUCMax;

void pGetLimits() {

	p_sint  siMinOne = -1;
	p_slint slMinOne = -1;
	p_schr  scMinOne = -1;

	pUIMax = *(p_uint*) (&siMinOne);
	pULMax = *(p_ulint*)(&slMinOne);
	pUCMax = *(p_uchr*) (&scMinOne);

	pSIMax = pUIMax/2;
	pSLMax = pULMax/2;
	pSCMax = pUCMax/2;

	pSIMin = -pSIMax - 1;
	pSLMin = -pSLMax - 1;
	pSCMin = -pSCMax - 1;

}

#endif
