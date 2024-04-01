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
 * === DEVNOTES ===
 * - These need to be implemented:
 *     _pbi_addb    NOT DONE
 *     _pbi_subb    NOT DONE
 *     _pbi_chr2dig DONE
 *     _pbi_dig2chr DONE
 *     pbi          DONE
 *     pbi_isnull   DONE
 *     pbi_isval    DONE
 *     pbi_fs       DONE
 *     pbi_isneg    DONE
 *     pbi_cmp      MISSING NEGATIVES
 *     pbi_add      MISSING NEGATIVES
 *     pbi_sub      MISSING NEGATIVES
 * - Consider multiplication and division.
 *
 * pbi_add and pbi_sub should operate their
 * respective operations only over positive integers.
 * Any negative number operations can, fundementally,
 * boil down to the positive number operations!
 *
 * pbi_sub has a lot of cases, that being
 * positives and negatives, and the first one being
 * greater, equal or smaller than the second one.
 *
 * Also, consider creating a struct like:
 *
 * typedef struct {
 *     pstr digits;
 *     pbool negative;
 * } pbi
 *
 * to store the PBI. This looks SIGNIFICANTLY
 * easier to work with, in contrast with the
 * sign being represented with the '-' in the string!
 */

#include "ptype.h"
#include "pcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This defines what type we are adding, subtracting,
 * and doing all other operations on the bigint.
 *
 * If you need great precision, use pulint.
 */
#ifndef P_BI_OP_TYPE
	#define P_BI_OP_TYPE puint
#endif

/* Used for _pbi_dig2chr */
pstr _pbi_digits = "0123456789";

/*
 * The bigint datatype
 * Essentially, a string
 */
typedef pstr pbi;

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
psint _pbi_chr2dig ( pchr chr ) {

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
pchr _pbi_dig2chr( pusint dig ) {
	if ( ( dig < 0 ) || ( dig > 9 ) ) return (pchr)0;
	return _pbi_digits[dig];
}

/* TODO */
pbi _pbi_addb() {}

/* TODO */
pbi _pbi_subb() {}

/* Checks if 'bi' is set to "0" */
pbool pbi_isnull( pbi bi ) { return (pbool)( strcmp(bi, "0") == 0 ); }

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
pbool pbi_isneg( pbi bi ) {

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
 * Takes an ALLOCATED BIT OF MEMORY,
 * reallocates it,
 * and adds/removes a minus.
 *
 * Assumes 'bi' is valid.
 *
 * Returns P_BADALLOC if allocation cannot be done.
 *
 * If "0" is passed, it isn't changed.
 */
pcode pbi_fs( pbi bi ) {

	pbool neg = pbi_isneg(bi);
	psz l = strlen(bi);
	psint i;
	pbi tmp;

	if ( pbi_isnull(bi) ) return P_SUCCESS;

	/*
	 * If the number is positive,
	 * reallocate space for one more character,
	 * and append a minus to the start.
	 */
	if ( !neg ) {

		/* l + minus + null terminator */
		tmp = (pbi)realloc(bi, (l + 2) * sizeof(pchr));

		if ( tmp == NULL ) {
			free(bi);
			return P_BADALLOC;
		}

		bi = tmp;

		for ( i = l + 1; i > 0; i-- ) {
			bi[i] = bi[i - 1];
		}

		bi[0] = '-';

		return P_SUCCESS;

	}

	/*
	 * The code below is what happens when the number is negative
	 *
	 * We shift the characters by one,
	 * deleting the minus
	 */

	for ( i = 0; i < l; i++ ) {
		bi[i] = bi[i + 1];
	}

	tmp = (pbi)realloc(bi, (l + 1) * sizeof(pchr));

	if ( tmp == NULL ) {
		free(bi);
		return P_BADALLOC;
	}

	bi = tmp;

	return P_SUCCESS;

}

/* TODO: Doc comment and negatives */
pcode pbi_cmp( pbi bi1, pbi bi2 ) {

	psz l1 = strlen(bi1);
	psz l2 = strlen(bi2);
	psz cmp;

	if ( l1 > l2 ) return P_GREATER;
	if ( l1 < l2 ) return P_SMALLER;

	/*
	 * This relies on the fact
	 * that the compiler is using ASCII.
	 * I *might* generalize the solution
	 * if a problem arises!
	 */

	cmp = strcmp(bi1, bi2);

	if ( cmp > 0 ) return P_GREATER;
	if ( cmp < 0 ) return P_SMALLER;
	return P_EQUAL;

}

/*
 * Returns a dynamically allocated string
 * containing the sum of the two bigints.
 *
 * Doesn't check the validity of the two bigints.
 *
 * The user is responsible for clearing the memory
 * of the returned string.
 */
pbi pbi_add( pbi bi1, pbi bi2 ) {

	pusint carry = 0, tmp;
	psint i;
	pstr s, ret, bibig;
	psz l1, l2, lbig, lsmall;

	l1 = strlen(bi1);
	l2 = strlen(bi2);

	if ( l1 > l2 ) { lbig = l1; lsmall = l2; bibig = bi1; }
	else           { lbig = l2; lsmall = l1; bibig = bi2; }

	/*
	 * The largest the new number can be is
	 * one larger than the bigger of the two numbers
	 *
	 * As an example: 99 + 99, two largest two-digit integers, result in 198
	 *
	 * s doesn't allocate space for a null terminator,
	 * since it's an array of characters,
	 * rather than a "real" C-style string
	 */
	s = (pstr)malloc( (lbig + 1) * sizeof(puchr) );
	if ( s == NULL ) return NULL;

	/* String from 1 so that we access the indeces of bi1 and bi2 properly */
	for ( i = 1; i <= lsmall; i++ ) {
		tmp = _pbi_chr2dig( bi1[l1 - i] ) + _pbi_chr2dig( bi2[l2 - i] ) + carry;
		s[i - 1] = _pbi_dig2chr( tmp % 10 );
		carry = tmp / 10;
	}

	/*
	 * After going across the digits in the smaller number,
	 * check that there's more digits.
	 *
	 * If there aren't, just add the carry to the last slot
	 *
	 * You'll notice this is similar to the for loop above,
	 * with the exception of it using bibig
	 */

	for ( ; i <= lbig; i++ ) {
		tmp = _pbi_chr2dig(bibig[lbig - i]) + carry;
		s[i - 1] = _pbi_dig2chr(tmp % 10);
		carry = tmp / 10;
	}

	/*
	 * Now, that we're at the ending, check for a carry
	 *
	 * The 'else' clause sets the variables up for
	 * the allocation and loop below
	 */
	if (carry != 0) { s[i-1] = _pbi_dig2chr(carry); }
	else            { i--; lbig--; }

	/*
	 * 'i' now points to the last index, where '\0' should be.
	 * We'll make a new string, and add the digits in reverse order!
	 */

	ret = (pstr)malloc( (i + 1)*sizeof(pchr) );
	if ( ret == NULL ) { free(s); return NULL; }

	ret[i] = '\0';
	for ( i-- ; i >= 0 ; i-- )
		ret[i] = s[lbig - i];

	free(s);
	return ret;

}

/*
 * Returns a dynamically allocated string
 * containing the difference of the two bigints.
 *
 * Doesn't check the validity of the two bigints.
 *
 * The user is responsible for clearing the memory
 * of the returned string.
 */
pbi pbi_sub(pbi bi1, pbi bi2) {

	pbi ret;
	psint i, j; /* TODO: Proper datatype? */
	psz lbig, lsmall;
	pstr s;
	pssint tmp;
	psint carry = 0; /* 1 if we carry, 0 if we don't ? */

	switch ( pbi_cmp( bi1, bi2 ) ) {

		case P_SMALLER:
			/*
			 * bi1 is smaller than bi2
			 * TODO: A function which flips the sign
			 *
			 * Return - ( pbi_sub( bi2, bi1 ) )
			 */
			break;

		case P_EQUAL:
			ret = (pbi)malloc(2 * sizeof(pchr));
			if ( ret == NULL ) return NULL;
			ret = (pbi)"0";
			return ret;

	}

	/*
	 * Since the two cases above call a return,
	 * this is what happens when bi1 > bi2
	 */

	/*
	 * We know that the bi1 has the same,
	 * if not more digits than bi2
	 */

	lbig = strlen(bi1);
	lsmall = strlen(bi2);

	/* No need to account for the null terminator */
	s = (pstr)malloc( lbig * sizeof(pchr) );
	if ( s == NULL ) return NULL;

	for ( i = 1; i <= lsmall; i++ ) {

		tmp = _pbi_chr2dig( bi1[lbig-i] ) - carry - _pbi_chr2dig( bi2[lsmall-i] );
		if ( tmp < 0 ) { carry = 1; tmp += 10; }
		else           { carry = 0; }

		s[i-1] = _pbi_dig2chr( tmp );

	}

	s[i-1] = _pbi_dig2chr( _pbi_chr2dig( bi1[lbig-i] ) - carry );
	i++;

	for ( ; i <= lbig; i++ ) { s[i-1] = bi1[lbig-i]; }

	/* Getting rid of trailing zeros */
	j = lbig - 1;
	while ( s[j] == '0' ) j--;
	/*
	 * 'j' now points to the index where the first
	 * index, from the back, which is non-zero
	 *
	 * We write from that one!
	 */

	/* +1 for the index to character count conversion, +1 for the null terminator */
	ret = (pbi)malloc( (j+2)*sizeof(pchr) );
	if ( ret == NULL ) { free(s); return NULL; }

	for ( i = 0 ; i <= j ; i++ )
		ret[i] = s[j - i];
	ret[j+1] = '\0';

	free(s);
	return ret;

}

#endif
