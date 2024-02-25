#ifndef PCLIB_BIGNUM
#define PCLIB_BIGNUM

/*
 * pbn.h
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
 *
 * === DEVNOTE ===
 * - These need to be implemented:
 *     pbn        DONE
 *     pbn_init   DONE
 *     pbn_isnull DONE
 *     pbn_cmp    DONE
 *     pbn_cmpN   DONE
 *     pbn_add
 *     pbn_addN
 *     pbn_sub
 *     pbn_subN
 * - Consider multiplication and division.
 * - Also, isn't this a bigint header, then, if there are no floating points?
 * - A BIGNUM IS ZERO ONLY WHEN THE SIZE OF 'dig' IS ZERO!
 *   Anything else would break the digit count checkers.
 */

#include <stdlib.h>
#include <stdio.h>

#include "./piarr.h"
#include "./ptype.h"
#include "./pcode.h"

/*
 * This defines what type we are adding, subtracting,
 * and doing all other operations on the bignum.
 *
 * If you need great precision, use pulint.
 */
#ifndef P_BIGNUM_OP_TYPE
#define P_BIGNUM_OP_TYPE puint
#endif

/* String-like bignum struct */
typedef struct {
	piarr(puchr) dig; /* Digits incremental dynamic array */
	pbool negative; /* A bool denoting if the number is negative */
} pbn;

/* Initializes the bignum to 0 */
pcode pbn_init( pbn* bignum ) {

	if ( bignum == NULL ) {
		bignum = (pbn*)malloc(sizeof(pbn));
		if ( bignum == NULL ) return P_BADALLOC;
	}
	piarr_init(bignum->dig);
	bignum->negative = P_FALSE;

	return P_SUCCESS;

}

/*
 * Checks if the bignum is zero
 *
 * This checks that the size of 'dig' is 0
 * TODO: Should this be a macro?
 */
pbool pbn_isnull( pbn bignum ) {
	return ( (bignum.dig).size == 0 );
}

/* Compares the two bignums */
pcode pbn_cmp( pbn* bignum1, pbn* bignum2 ) {

	psint i;

	/* If both the bignums are of size 0, they're equal */
	if ( (bignum1->dig).size == 0 && (bignum2->dig).size == 0 ) return P_EQUAL;

	/* If the bignums are of opposite signs, the positive one is bigger */
	if ( bignum1->negative != bignum2->negative )
		return ( bignum1->negative ? P_SMALLER : P_GREATER );

	/* The bigger one has more digits */
	if ( (bignum1->dig).size > (bignum2->dig).size ) return P_GREATER;
	if ( (bignum1->dig).size < (bignum2->dig).size ) return P_SMALLER;

	/* The last option is to check the values of the digits, greatest to weakest */
	for ( i = (bignum1->dig).size - 1; i >= 0; i-- ) {
		if ( ((bignum1->dig).data)[i] > ((bignum2->dig).data)[i] ) return P_GREATER;
		if ( ((bignum1->dig).data)[i] < ((bignum2->dig).data)[i] ) return P_SMALLER;
	}

	return P_EQUAL;

}

/* Compares the bignum and number */
pcode pbn_cmpN( pbn bignum, P_BIGNUM_OP_TYPE num ) {

	psint pNumDigitCount = 0;
	psint pCompIter;
	puchr* numFlipped;
	P_BIGNUM_OP_TYPE numTmp = num;

	/* If both the bignum and num are 0, return 0 */
	if ( (bignum.dig).size == 0 && num == 0 ) return P_EQUAL;

	/* If the bignum is negative, it's smaller */
	if ( bignum.negative ) return P_SMALLER;

	/* Counting the number of digits in num */
	while ( numTmp != 0 ) { pNumDigitCount++; numTmp /= 10; }

	/* If bignum has more digits, it's bigger, and vice-versa */
	if ( (bignum.dig).size > pNumDigitCount ) return P_GREATER;
	if ( (bignum.dig).size < pNumDigitCount ) return P_SMALLER;

	numFlipped = (puchr*)calloc(pNumDigitCount, sizeof(puchr));
	if ( numFlipped == NULL ) return P_BADALLOC;

	numTmp = num;

	/*
	 * We're flipping the 'num' argument, so that the greatest digit is at index 0.
	 * This way, we can compare the digits, greatest to weakest
	 */
	for ( pCompIter = 0; pCompIter < pNumDigitCount; pCompIter++ ) {
		numFlipped[pCompIter] = numTmp % 10;
		numTmp /= 10;
	}

	for ( pCompIter = (bignum.dig).size - 1; pCompIter >= 0; pCompIter-- ) {

		if ( ((bignum.dig).data)[pCompIter] > numFlipped[pCompIter] ) {
			free(numFlipped);
			return P_GREATER;
		}

		if ( ((bignum.dig).data)[pCompIter] < numFlipped[pCompIter] ) {
			free(numFlipped);
			return P_SMALLER;
		}

	}

	free(numFlipped);
	return P_EQUAL;

}

/*
 * Clears the memory of the bignum,
 * and sets the variables back to NULL and P_FALSE.
 */
pnoret pbn_clean( pbn bignum ) {
	piarr_clean(bignum.dig);
	bignum.negative = P_FALSE;
}

/*
 * Adds the bignum addend to the bignum
 *
 * The first bignum is changed directly
 * TODO: Is this a good idea?
 */
void pbn_add( pbn* bignum, pbn* addend ) {

}

/*
 * Adds the integer addend to the bignum
 *
 * The bignum is changed directly
 */
pnoret pbn_addN( pbn* bignum, P_BIGNUM_OP_TYPE addend ) {

	P_BIGNUM_OP_TYPE pAddendIter = addend;
	puchr pCarry = 0;
	puchr pTmp;

	pusint i;

	/*
	 * The number is negative
	 */

	if ( bignum->negative ) {



	}

	/* The number is positive, we do basic addition with carrying over */

	else {

		for ( i = 0; pAddendIter != 0; i++ ) {

			if ( i == (bignum->dig).size ) {
				piarr_add(bignum->dig, 0);
				if ( (bignum->dig).data == NULL ) return;
			}

			pTmp = ((bignum->dig).data)[i] + ( pAddendIter % 10 ) + pCarry;

			((bignum->dig).data)[i] = pTmp % 10;

			pCarry = pTmp / 10;

			pAddendIter /= 10;

		}

		if ( pCarry != 0 ) {
			piarr_add(bignum->dig, pCarry);
			if ( (bignum->dig).data == NULL ) return;
		}

	}

}

#endif
