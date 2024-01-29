#ifndef PCLIB_BIGNUM
#define PCLIB_BIGNUM

/*
 * pbignum.h
 *
 * Implementation of a string-like integer bignum
 *
 * As it is VERY apparent, this implementation is VERY wasteful,
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
#define p_bignumOpType p_uint

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
}

/*
 * Adds the integer addend to the bignum
 *
 * The bignum is changed directly
 */
void pBigNumAddNum( p_bignum* bignum, p_bignumOpType addend ) {

}

/*
 * Adds the integer bignum addend to the bignum
 *
 * The first bignum is changed directly
 */
void pBigNumAddBignum( p_bignum* bignum, p_bignum addend ) {

}

#endif
