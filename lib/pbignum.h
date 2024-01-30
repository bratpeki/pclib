#ifndef PCLIB_BIGNUM
#define PCLIB_BIGNUM

/*
 * pbignum.h
 *
 * Implementation of a string-like integer bignum
 *
 * As is VERY apparent, this implementation is VERY wasteful,
 * due to it using one byte per digit. Sadly, ISO C doesn't specify
 * headers like stdint.h, which would let us have data with a specified
 * size. However, I still wanted to implement something regarding this,
 * and despite being VERY badly optimized for memory, it'll do the job.
 *
 * The implementation uses my incremental dynamic array, so
 * THERE IS A NEED TO CHECK THE MEMORY REALLOCATION SUCCESS!
 */

#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>

#include "./pidynarr.h"
#include "./ptypes.h"
#include "./pcodes.h"

/*
 * This defines what type we are adding, subtracting,
 * and doing all other operations on the bignum.
 *
 * If you need great precision, use p_ulint.
 */
#ifndef p_bignumOpType
#define p_bignumOpType p_uint
#endif

/* String-like bignum struct */
typedef struct {
	p_idynarr(p_uchr) dig; /* Digits incremental dynamic array */
	p_bool negative; /* A bool denoting if the number is negative */
} p_bignum;

/* Initializes the bignum to 0 */
int pBigNumInit( p_bignum* bignum ) {

	if ( bignum == NULL ) {
		bignum = (p_bignum*)malloc(sizeof(p_bignum));
		if ( bignum == NULL ) return P_BADALLOC;
	}

	pIDynArrInit(bignum->dig);
	bignum->negative = p_false;

	return P_SUCCESS;

}

/*
 * Clears the memory of the bignum,
 * and sets the variables back to NULL and p_false.
 */
void pBigNumCleanup( p_bignum bignum ) {
	pIDynArrCleanup(bignum.dig);
	bignum.negative = p_false;
}

/*
 * Adds the integer addend to the bignum
 *
 * The bignum is changed directly
 */
void pBigNumAddNum( p_bignum* bignum, p_bignumOpType addend ) {

	p_bignumOpType pAddendIter = addend;
	p_uchr pCarry = 0;
	p_uchr pTmp;

	p_usint i;

	for ( i = 0; pAddendIter != 0; i++ ) {

		printf("loop i = %d, pAddendIter = %d\n", i, pAddendIter);
		printf("  dig.size = %d\n", (bignum->dig).size);

		if ( i == (bignum->dig).size ) {
			pIDynArrAdd(bignum->dig, 0);
			if ( (bignum->dig).data == NULL ) return;
		}

		printf(
			"  pTmp = ((bignum->dig).data)[i] + ( pAddendIter %% 10 ) + carry\n"
			"             = %d + %d + %d\n",
			((bignum->dig).data)[i], pAddendIter % 10, pCarry
		);
		pTmp = ((bignum->dig).data)[i] + ( pAddendIter % 10 ) + pCarry;

		printf("  bignum dig data [i] = %d\n", pTmp % 10);
		((bignum->dig).data)[i] = pTmp % 10;

		printf("  carry = %d\n", pTmp % 10);
		pCarry = pTmp / 10;

		pAddendIter /= 10;

		printf("loop end\n\n");

	}

	if ( pCarry != 0 ) {
		pIDynArrAdd(bignum->dig, pCarry);
		if ( (bignum->dig).data == NULL ) return;
	}

}

/*
 * Adds the integer bignum addend to the bignum
 *
 * The first bignum is changed directly
 */
void pBigNumAddBignum( p_bignum* bignum, p_bignum addend ) {

}

#endif
