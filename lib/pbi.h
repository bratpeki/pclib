#ifndef PCLIB_BI
#define PCLIB_BI

/*
 * pbi.h
 *
 * Implementation of a string bigint
 *
 * As is VERY apparent, this implementation is VERY wasteful,
 * due to it using one char per digit. Sadly, ISO C doesn't specify
 * headers like stdint.h, which would let us have data with a specified
 * size. However, I still wanted to implement something regarding this,
 * and despite being VERY badly optimized for memory, it'll do the job.
 *
 * This was once made with dynamic allocation in mind. However, doing
 * memchecks after each operations is, needless to say, not pleasant.
 * So a bigint is now a fixed-size array.
 *
 * TODO: Consider multiplication, mod and division.
 *
 * TODO: Are zeros at the start of the bignum valid?
 *
 * TODO: bisize must always be at least 2
 */

#include "ptype.h"
#include "pcode.h"
#include "pstr.h"

#include <stdlib.h>
#include <string.h>

/* Used for _pbi_d2c */
pstr _pbi_digits = "0123456789";

/*
 * The bigint datatype
 * Essentially, a char
 *
 * A bigint is defined with:
 * pbi num[100];
 *
 * When passed to functions, it's passed as
 * type name( pbi* num, int numsize )
 *
 * In the case above, 'numsize' is 100
 */
typedef pchr pbi;

/*
 * A reliable char-to-digit converter.
 *
 * Some compilers don't use ASCII, so I made this!
 * For ASCII, conversion is as simple as:
 *
 * return (chr - '0');
 *
 * Returns -1 if the digit isn't valid
 */
psint _pbi_c2d( pchr chr ) {

	switch ( chr ) {

		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default:  return -1;

	}

}

/*
 * A reliable digit-to-char converter.
 *
 * Some compilers don't use ASCII, so I made this!
 *
 * Return (pchr)0 if the digit is out-of-range.
 */
pchr _pbi_d2c( pusint dig ) {
	if ( ( dig < 0 ) || ( dig > 9 ) ) return (pchr)0;
	return _pbi_digits[dig];
}

/*
 * Base addition function
 *
 * Adds two positive bigints and returns the result.
 * If memory cannot be allocated, returns NULL.
 *
 * Returns P_SUCCESS if all goes well.
 * Returns P_OUTOFBOUNDS if the 'sum' array isn't large enough to house the sum.
 */
pcode _pbi_addb( pbi* op1, pbi* op2, pbi* sum, psz bisize ) {

	pusint carry = 0, tmp;
	psz i;
	pbi* bibig;
	psz l1, l2, lbig, lsmall;

	l1 = strlen(op1);
	l2 = strlen(op2);

	memset(sum, 0, bisize);

	if ( l1 > l2 ) { lbig = l1; lsmall = l2; bibig = op1; }
	else           { lbig = l2; lsmall = l1; bibig = op2; }

	/* bisize includes the null terminator, the max length is that minus 1 */
	if ( bisize - 1 < lbig ) return P_OUTOFBOUNDS;

	/* Addition over the common indeces */
	for ( i = 1; i <= lsmall; i++ ) {
		tmp = _pbi_c2d( op1[l1 - i] ) + _pbi_c2d( op2[l2 - i] ) + carry;
		sum[i - 1] = _pbi_d2c( tmp % 10 );
		carry = tmp / 10;
	}

	/*
	 * After going across the common indeces,
	 * handle the indeces of the larger bigint.
	 */

	for ( ; i <= lbig; i++ ) {
		tmp = _pbi_c2d(bibig[lbig - i]) + carry;
		sum[i - 1] = _pbi_d2c(tmp % 10);
		carry = tmp / 10;
	}

	/* Now that we're at the ending, check for a carry. */
	if ( carry != 0 ) {
		if ( lbig + 1 <= bisize ) return P_OUTOFBOUNDS;
		sum[i-1] = _pbi_d2c(carry);
	}

	/* We filled everything to zeros before, we can flip this safely */
	pstr_flip(sum);

	return P_SUCCESS;

}

/*
 * Base subtraction function
 *
 * Subtracts two positive bigints and returns the result.
 * If memory cannot be allocated, returns NULL.
 *
 * The first bigint has to be larger.
 * This is not checked.
 *
 * All three bigints must be of the same size, bisize
 */
pnoret _pbi_subb( pbi* op1, pbi* op2, pbi* diff, psz bisize ) {

	psz i;
	psz lbig, lsmall;
	pssint tmp;
	psint carry = 0; /* 1 if we carry, 0 if we don't ? */

	/*
	 * We know that the bi1 has
	 * the same number of,
	 * if not more digits than bi2
	 */

	lbig = strlen(op1);
	lsmall = strlen(op2);

	memset(diff, 0, bisize);

	/*
	 * Similarly to _pbi_addb,
	 * we go through common indeces,
	 * and then handle the rest.
	 */
	for ( i = 1; i <= lsmall; i++ ) {

		tmp = _pbi_c2d( op1[lbig-i] ) - carry - _pbi_c2d( op2[lsmall-i] );

		if ( tmp < 0 ) { carry = 1; tmp += 10; }
		else           { carry = 0; }

		diff[i-1] = _pbi_d2c( tmp );

	}

	diff[i-1] = _pbi_d2c( _pbi_c2d( op1[lbig-i] ) - carry );
	i++;

	for ( ; i <= lbig; i++ ) { diff[i-1] = op1[lbig-i]; }

	pstr_flip(diff);

}

/* Checks if 'bi' is set to "0" */
pbool pbi_isnull( pbi* bi ) { return (pbool)( strcmp(bi, "0") == 0 ); }

/*
 * Checks if the bigint is negative,
 * by checking the sign, as well as the fact
 * that there's more than 0 digits after the sign
 *
 * Zero isn't negative!
 */
pbool pbi_isneg( pbi* bi ) {

	/* Sign and at least one digit */
	if ( strlen(bi) >= 2 ) return (pbool)( bi[0] == '-' );

	/*
	 * In any other case,
	 * there's not enough space for a sign and
	 * at least one digit,
	 * so it can't be valid and negative!
	 */
	return P_FALSE;

}

/*
 * Flips the sign of the bigint.
 *
 * If the array is filled to the brim with digits,
 * and a minus cannot be added to the positive bignum,
 * return P_OUTOFBOUNDS. Otherwise, returns P_SUCCESS;
 */
pcode pbi_fs( pbi* bi, psz bisize ) {

	psz l = strlen(bi);
	psint i;

	if ( pbi_isnull(bi) ) return P_SUCCESS;

	if ( bi[0] != '-' ) { /* Positive */

		/*
		 * We can't add a minus to
		 *   pbi a[5] = "1234"
		 */
		if ( l == bisize - 1 ) return P_OUTOFBOUNDS;

		for ( i = l; i > 0; i-- )
			bi[i] = bi[i-1];
		bi[0] = '-';

	}

	else { /* Negative */

		i = 0;

		while ( i < l-1 ) {
			bi[i+1] = bi[i];
			i++;
		}

	}

	return P_SUCCESS;

}

/*
 * Compares two numbers and returns the following:
 *
 * P_GREATER if bi1 is greater,
 * P_SMALLER if bi1 is smaller and
 * P_EQUAL if they're equal.
 */
pcode pbi_cmp( pbi* bi1, pbi* bi2, psz bisize ) {

	pbool bi1neg, bi2neg;
	psz l1 = strlen(bi1);
	psz l2 = strlen(bi2);
	pbi *bi1abs, *bi2abs;
	psint i;

	bi1neg = pbi_isneg(bi1);
	bi2neg = pbi_isneg(bi2);

	if ( bi1neg && !bi2neg ) return P_SMALLER;
	if ( !bi1neg && bi2neg ) return P_GREATER;

	if ( !bi1neg && !bi2neg ) {

		if ( l1 > l2 ) { return P_GREATER; }
		if ( l1 < l2 ) { return P_SMALLER; }

		for ( i = 0; i < l1 ; i++ )
			if ( bi1[i] != bi2[i] )
				return (
					( _pbi_c2d(bi1[i]) > _pbi_c2d(bi2[i]) )
					? P_GREATER : P_SMALLER
				);

	}

	else if ( bi1neg && bi2neg ) {

		if ( l1 < l2 ) { return P_GREATER; }
		if ( l1 > l2 ) { return P_SMALLER; }

		bi1abs = bi1 + sizeof(pchr);
		bi2abs = bi2 + sizeof(pchr);

		for ( i = 0; i < l1 - 1 ; i++ )
			if ( bi1abs[i] != bi2abs[i] )
				return (
					( _pbi_c2d(bi1abs[i]) < _pbi_c2d(bi2abs[i]) )
					? P_GREATER : P_SMALLER
				);

	}

	return P_EQUAL;

}

/*
 * Adds 'op1' and 'op2' together and adds the result to 'sum'.
 *
 * All bigints must be of the same size, bisize.
 *
 * TODO: Exit codes
 */
pcode pbi_add( pbi* op1, pbi* op2, pbi* sum, psz bisize ) {

	pbool neg1, neg2;
	pbi *biabs, *biother, *biabs2;

	neg1 = pbi_isneg(op1);
	neg2 = pbi_isneg(op2);

	if ( !neg1 && !neg2 ) return _pbi_addb(op1, op2, sum, bisize);

	if ( neg1 && neg2 ) {

		/* Absolute values */
		biabs = op1 + sizeof(pchr);
		biabs2 = op2 + sizeof(pchr);

		if ( _pbi_addb(biabs, biabs2, sum, bisize) == P_OUTOFBOUNDS ) return P_OUTOFBOUNDS;
		if ( pbi_fs(sum, bisize) == P_OUTOFBOUNDS ) return P_OUTOFBOUNDS;

		return P_SUCCESS;

	}

	else if ( neg1 && !neg2 ) {
		biabs = op1 + sizeof(pchr);
		biother = op2;
	}

	else if ( !neg1 && neg2 ) {
		biother = op1;
		biabs = op2 + sizeof(pchr);
	}

	/*               a      b                 */
	switch ( pbi_cmp(biabs, biother, bisize) ) {

		case P_EQUAL:
			/* TODO bisize >= 2 */
			memcpy(sum, "0", 2);
			break;

		case P_GREATER:
			/* -a + b = -(a-b) */
			_pbi_subb(biabs, biother, sum, bisize);
			if ( pbi_fs(sum, bisize) == P_OUTOFBOUNDS ) return P_OUTOFBOUNDS;
			break;

		case P_SMALLER:
			/* -a + b = b-a */
			_pbi_subb(biother, biabs, sum, bisize);
			break;

	}

	return P_SUCCESS;

}

/*
 * Returns a dynamically allocated string
 * containing the difference of the two bigints.
 *
 * Doesn't check the validity of the two input bigints.
 *
 * All bigints must be of the same size, bisize.
 *
 * The user is responsible for clearing the memory
 * of the returned string.
 */
pcode pbi_sub( pbi* op1, pbi* op2, pbi* diff, psz bisize ) {

	pbool neg1, neg2;

	if ( pbi_cmp(op1, op2, bisize) == P_EQUAL ) {
		/* TODO: bisize >= 2 */
		memcpy(diff, "0", 2);
		return P_SUCCESS;
	}

	neg1 = pbi_isneg(op1);
	neg2 = pbi_isneg(op2);

	/* |a|-|b| = a-b */
	if ( !neg1 && !neg2 ) {

		/* 5 - 3 = 2 */
		if ( pbi_cmp(op1, op2, bisize) == P_GREATER ) {
			_pbi_subb(op1, op2, diff, bisize);
		}

		/* 3 - 5 = -(5-3) = -2 */
		else {
			_pbi_subb(op2, op1, diff, bisize);
			if ( pbi_fs(diff, bisize) == P_OUTOFBOUNDS ) return P_OUTOFBOUNDS;
		}

	}

	/* |a|-|b| = a + b */
	else if ( !neg1 && neg2 ) {
		if ( pbi_add(op1, op2+sizeof(pchr), diff, bisize) == P_OUTOFBOUNDS )
			return P_OUTOFBOUNDS;
	}

	/* |a|-|b| = -a - b = -(a+b) */
	else if ( neg1 && !neg2 ) {
		if ( pbi_add(op1+sizeof(pchr), op2, diff, bisize) == P_OUTOFBOUNDS ) return P_OUTOFBOUNDS;
		if ( pbi_fs(diff, bisize) == P_OUTOFBOUNDS ) return P_OUTOFBOUNDS;
	}

	/*
	 * Both negative
	 *
	 * |a|-|b| = -a + b = b-a
	 */
	else {

		/* -5 - (-3) = 3 - 5 */
		if ( pbi_cmp(op1+sizeof(pchr), op2+sizeof(pchr), bisize) == P_GREATER ) {
			_pbi_subb(op1+sizeof(pchr), op2+sizeof(pchr), diff, bisize);
			if ( pbi_fs(diff, bisize) == P_OUTOFBOUNDS ) return P_OUTOFBOUNDS;
		}

		/* -3 - (-5) = 5 - 3 */
		else _pbi_subb(op2, op1, diff, bisize);

	}

	return P_SUCCESS;

}

#endif
