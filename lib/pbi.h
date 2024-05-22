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
 *
 *     pbi        DONE
 *     _pbi_c2d   DONE
 *     _pbi_d2c   DONE
 *     pbi_isnull DONE
 *     pbi_fs     DONE
 *     pbi_isneg  DONE
 *     pbi_isval  DONE
 *     _pbi_addb  DONE
 *     _pbi_subb  DONE
 *     pbi_add    DONE
 *     pbi_cmp    DONE
 *     pbi_sub    DONE
 *
 * TODO: Don't accomodate solutions for ASCII,
 * make everything universal
 *
 * - Move from allocated memory to data memory
 * - Consider multiplication, mod and division.
 */

#include "ptype.h"
#include "pcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Used for _pbi_d2c */
pstr _pbi_digits = "0123456789";

/*
 * The bigint datatype
 * Essentially, a string
 */
typedef pstr pbi;

/*
 * A single digit in the bigint
 * Essentially, a char
 */
typedef pchr pbid;

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
psint _pbi_c2d ( pchr chr ) {

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
 */
pbi _pbi_addb( pbi bi1, pbi bi2 ) {

	pusint carry = 0, tmp;
	psint i;
	pstr s, ret;
	pbi bibig;
	psz l1, l2, lbig, lsmall;

	l1 = strlen(bi1);
	l2 = strlen(bi2);

	if ( l1 > l2 ) { lbig = l1; lsmall = l2; bibig = bi1; }
	else           { lbig = l2; lsmall = l1; bibig = bi2; }

	/*
	 * The largest the new number can be is
	 * one larger than the bigger of the two numbers.
	 *
	 * As an example: 99 + 99, two largest two-digit integers, result in 198
	 *
	 * 's' doesn't allocate space for a null terminator,
	 * since it's an array of characters,
	 * rather than a "real" C-style string.
	 * Later down the line, a proper C-style
	 * string is generated.
	 */
	s = (pstr)malloc( (lbig + 1) * sizeof(pchr) );
	if ( s == NULL ) return NULL;

	/* Addition over the common indeces */
	for ( i = 1; i <= lsmall; i++ ) {
		tmp = _pbi_c2d( bi1[l1 - i] ) + _pbi_c2d( bi2[l2 - i] ) + carry;
		s[i - 1] = _pbi_d2c( tmp % 10 );
		carry = tmp / 10;
	}

	/*
	 * After going across the common indeces,
	 * handle the indeces of the larger bigint.
	 */

	for ( ; i <= lbig; i++ ) {
		tmp = _pbi_c2d(bibig[lbig - i]) + carry;
		s[i - 1] = _pbi_d2c(tmp % 10);
		carry = tmp / 10;
	}

	/*
	 * Now that we're at the ending, check for a carry.
	 *
	 * The 'else' clause sets the variables up for
	 * the allocation and loop below
	 */
	if (carry != 0) { s[i-1] = _pbi_d2c(carry); }
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
 * Base subtraction function
 *
 * Subtracts two positive bigints and returns the result.
 * If memory cannot be allocated, returns NULL.
 *
 * The first bigint has to be larger
 * This is not checked.
 */
pbi _pbi_subb( pbi bi1, pbi bi2 ) {

	pbi ret;
	psint i, j; /* TODO: Proper datatype? */
	psz lbig, lsmall;
	pstr s;
	pssint tmp;
	psint carry = 0; /* 1 if we carry, 0 if we don't ? */

	/*
	 * We know that the bi1 has
	 * the same number of,
	 * if not more digits than bi2
	 */

	lbig = strlen(bi1);
	lsmall = strlen(bi2);

	/*
	 * No need to account for
	 * the string terminator,
	 * much like in _pbi_addb.
	 */
	s = (pstr)malloc( lbig * sizeof(pchr) );
	if ( s == NULL ) return NULL;

	/*
	 * Similarly to _pbi_addb,
	 * we go through common indeces,
	 * and then handle the rest.
	 */
	for ( i = 1; i <= lsmall; i++ ) {

		tmp = _pbi_c2d( bi1[lbig-i] ) - carry - _pbi_c2d( bi2[lsmall-i] );
		if ( tmp < 0 ) { carry = 1; tmp += 10; }
		else           { carry = 0; }

		s[i-1] = _pbi_d2c( tmp );

	}

	s[i-1] = _pbi_d2c( _pbi_c2d( bi1[lbig-i] ) - carry );
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

/* Checks if 'bi' is set to "0" */
pbool pbi_isnull( pbi bi ) { return (pbool)( strcmp(bi, "0") == 0 ); }

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

/* TODO: Doc comment */
pcode pbi_cmp( pbi bi1, pbi bi2 ) {

	pbool bi1neg, bi2neg;
	psz l1 = strlen(bi1);
	psz l2 = strlen(bi2);
	pbi bi1abs, bi2abs;
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
 * TODO: Returning "0" doesn't require a NULL-check.
 */
pbi pbi_add( pbi bi1, pbi bi2 ) {

	pbi ret;
	pbool neg1, neg2;
	pbi biabs;
	pbi biother;

	neg1 = pbi_isneg(bi1);
	neg2 = pbi_isneg(bi2);

	if ( !neg1 && !neg2 ) {
		ret = _pbi_addb(bi1, bi2);
	}

	else if ( neg1 && neg2 ) {
		ret = _pbi_addb( bi1 + sizeof(pchr) , bi2 + sizeof(pchr));
		if ( ret != NULL ) pbi_fs(ret);
	}

	else if ( neg1 && !neg2 ) {
		biabs = bi1 + sizeof(pchr);
		biother = bi2;
	}
	else if ( !neg1 && neg2 ) {
		biother = bi1;
		biabs = bi2 + sizeof(pchr);
	}

	switch (pbi_cmp(biabs, biother) ) {

		/* TODO: This */
		case P_EQUAL:
			ret = (pbi)calloc(2, sizeof(pchr));
			if (ret != NULL) strcpy(ret, "0");
			break;

		case P_GREATER:
			/* -a + b = -(a-b) */
			ret = _pbi_subb(biabs, biother);
			pbi_fs(ret);
			break;

		case P_SMALLER:
			/* -a + b = b-a */
			ret = _pbi_subb(biother, biabs);
			break;

	}

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
 *
 * TODO: This fails for constant strings.
 *       Consider using exclusively const char* strings.
 */
pbi pbi_sub(pbi bi1, pbi bi2) {

	pbi ret;

	pbi_fs(bi2);
	if ( bi2 == NULL ) return NULL;

	ret = pbi_add(bi1, bi2);

	pbi_fs(bi2);
	if ( bi2 == NULL ) return NULL;

	return ret;

}

#endif
