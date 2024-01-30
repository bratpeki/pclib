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
 * Compares the two numbers
 *
 * Returns 0 if they're equal,
 * and the number of the argument which is greater if they're not
 */
int pBigNumCompNum( p_bignum bignum, p_bignumOpType num ) {

	p_sint pNumDigitCount = 0;
	p_bignumOpType numTmp = num;
	p_sint pCompIter;
	p_idynarr(p_uchr) numFlipped;

	/* If both the bignum and num are 0, return 0 */
	if ( (bignum.dig).size == 0 && num == 0 ) return 0;

	/* If the bignum is negative, it's smaller */
	if ( bignum.negative ) return 2;

	/* Counting the number of digits in num */
	while ( numTmp != 0 ) { pNumDigitCount++; numTmp /= 10; }

	/* If bignum has more digits, it's bigger, and vice-versa */
	if ( (bignum.dig).size > pNumDigitCount ) return 1;
	if ( (bignum.dig).size < pNumDigitCount ) return 2;

	numFlipped.data = (p_uchr*)calloc(3, sizeof(p_uchr));
	numFlipped.size = pNumDigitCount;

	numTmp = num;

	for ( pCompIter = 0; pCompIter < pNumDigitCount; pCompIter++ ) {
		(numFlipped.data)[pCompIter] = numTmp % 10;
		numTmp /= 10;
	}

	for ( pCompIter = (bignum.dig).size - 1; pCompIter >= 0; pCompIter-- ) {

		if ( ((bignum.dig).data)[pCompIter] > (numFlipped.data)[pCompIter] ) return 1;
		if ( ((bignum.dig).data)[pCompIter] < (numFlipped.data)[pCompIter] ) return 2;

	}

	return 0;

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

	/*
	 * The number is negative
	 */

	if ( bignum->negative ) {



	}

	/* The number is positive, we do basic addition with carrying over */

	else {

		for ( i = 0; pAddendIter != 0; i++ ) {

			if ( i == (bignum->dig).size ) {
				pIDynArrAdd(bignum->dig, 0);
				if ( (bignum->dig).data == NULL ) return;
			}

			pTmp = ((bignum->dig).data)[i] + ( pAddendIter % 10 ) + pCarry;

			((bignum->dig).data)[i] = pTmp % 10;

			pCarry = pTmp / 10;

			pAddendIter /= 10;

		}

		if ( pCarry != 0 ) {
			pIDynArrAdd(bignum->dig, pCarry);
			if ( (bignum->dig).data == NULL ) return;
		}

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
