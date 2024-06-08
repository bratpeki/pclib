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
 * === DEVNOTES ===
 *
 * TODO: LET THE USER KNOW THEY (maybe) SHOULDN'T USE CONST STRINGS AS PARAMS!
 *
 * TODO: Don't accomodate solutions for ASCII,
 * make everything universal
 *
 * - Move from allocated memory to data memory
 * - Consider multiplication, mod and division.
 */

#include "ptype.h"
#include "pcode.h"
#include "pstr.h"

#include <stdio.h>
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
 * TODO: Implement escape codes for array overflows
 */
pcode _pbi_addb( pbi* op1, pbi* op2, pbi* sum, psz bisize ) {

	pusint carry = 0, tmp;
	psint i;
	pbi* bibig;
	psz l1, l2, lbig, lsmall;

	l1 = strlen(op1);
	l2 = strlen(op2);

	memset(sum, 0, bisize);

	if ( l1 > l2 ) { lbig = l1; lsmall = l2; bibig = op1; }
	else           { lbig = l2; lsmall = l1; bibig = op2; }

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
	if (carry != 0)
		sum[i-1] = _pbi_d2c(carry);

	pstr_flip(sum);

	return P_SUCCESS;

}

/*
 * Base subtraction function
 *
 * Subtracts two positive bigints and returns the result.
 * If memory cannot be allocated, returns NULL.
 *
 * The first bigint has to be larger
 * This is not checked.
 */
pnoret _pbi_subb( pbi* op1, pbi* op2, pbi* diff, psz bisize ) {

	psint i; /* TODO: Proper datatype? */
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

/* TODO: Try changing the code above with a !strcmp */

/*
 * Returns P_TRUE if 'val' is in a valid format for a bigint,
 * and P_FALSE if it isn't
 *
 * The proper format is:
 * (OPTIONAL '-') + (SERIES OF DIGITS) + '\0'
 *
 * Trailing zeros aren't allowed.
 * 'val' can't be NULL or an empty string
 * It can't just be a minus.
 *
 * TODO: Deprecate this, honestly.
 */
pbool pbi_isval( pstr val ) {

	puint i = 0;

	/* Obviously! */
	if ( val == NULL ) return P_FALSE;

	/* An empty string isn't a bigint */
	if ( val[0] == '\0' ) return P_FALSE;

	/* Obviously! Part 2! */
	if ( !strcmp(val, "-") ) return P_FALSE;

	i = ( val[0] == '-' ) ? 1 : 0;

	/*
	 * If there's more than one digit,
	 * or a minus, followed by digits,
	 * and the first digit is zero,
	 * then there's a trailing zero
	 */
	if ( strlen(val) > 1 )
		if ( val[i] == '0' )
			return P_FALSE;

	for ( ; val[i] != '\0'; i++ ) {

		switch ( val[i] ) {

			/*
			 * This would be easier with an if statement:
			 * if ( (val[i] >= '0') && (val[i] <= '9') )
			 * This applies to the ASCII values, so
			 * I generalized it
			 */

			case '0': case '1': case '2':
			case '3': case '4': case '5':
			case '6': case '7': case '8':
			case '9': break;

			default: return P_FALSE;

		}

	}

	return P_TRUE;

}

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

		for ( i = 0; i < l; i++ )
			bi[ i+1 ] = bi[i];
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

/* TODO: Doc comment */
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
 * Returns a dynamically allocated string
 * containing the sum of the two bigints.
 *
 * Doesn't check the validity of the two bigints.
 *
 * The user is responsible for clearing the memory
 * of the returned string, as well as the NULL-check.
 *
 * TODO: Update this comment
 */
pcode pbi_add( pbi* op1, pbi* op2, pbi* sum, psz bisize ) {

	pbool neg1, neg2;
	pbi *biabs, *biother, *biabs2;
	pcode ret;

	neg1 = pbi_isneg(op1);
	neg2 = pbi_isneg(op2);

	if ( !neg1 && !neg2 )
		return _pbi_addb(op1, op2, sum, bisize);

	if ( neg1 && neg2 ) {

		/* Can't flip signs on constants */
		biabs = op1 + sizeof(pchr);
		biabs2 = op2 + sizeof(pchr);

		ret = _pbi_addb(biabs, biabs2, sum, bisize);
		/* TODO: Handle 'ret' and 'pbi_fs' return value */
		pbi_fs(sum, bisize);
		return ret;

	}

	else if ( neg1 && !neg2 ) {
		biabs = op1 + sizeof(pchr);
		biother = op2;
	}

	else if ( !neg1 && neg2 ) {
		biother = op1;
		biabs = op2 + sizeof(pchr);
	}

	switch ( pbi_cmp(biabs, biother, bisize) ) {

		/* TODO: This */
		case P_EQUAL:
			memcpy(sum, "0", 2);
			break;

		case P_GREATER:
			/* -a + b = -(a-b) */
			_pbi_subb(biabs, biother, sum, bisize);
			if ( pbi_fs(sum, bisize) )
				return P_OUTOFBOUNDS;

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
 * Doesn't check the validity of the two bigints.
 *
 * The user is responsible for clearing the memory
 * of the returned string.
 *
 * TODO: This fails for constant strings.
 *       Consider using exclusively const char* strings.
 */
pcode pbi_sub( pbi* op1, pbi* op2, pbi* diff, psz bisize ) {

	/*
	 * Use isnull checks and +sizeof(pchr) to make it work for constant strings
	 */

	/*
	pbi ret;

	pbi_fs(bi2);
	if ( bi2 == NULL ) return NULL;

	ret = pbi_add(bi1, bi2);

	pbi_fs(bi2);
	if ( bi2 == NULL ) return NULL;

	return ret;
	*/

	return P_SUCCESS;

}

#endif
