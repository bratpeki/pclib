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
 * The implementation uses my incremental dynamic array, so
 * THERE IS A NEED TO CHECK THE MEMORY REALLOCATION SUCCESS!
 *
 * === DEVNOTES ===
 * - These need to be implemented:
 *     pbi        DONE
 *     pbi_isnull DONE
 *     pbi_isneg  DONE
 *     pbi_cmp    DONE
 *     pbi_cmpN   DONE
 *     pbi_add
 *     pbi_addN
 *     pbi_sub
 *     pbi_subN
 * - Consider multiplication and division.
 *
 * pbi_add(N) and pbi_sub(N) should operate their
 * respective operations only over positive integers.
 * Any negative number operations can, fundementally,
 * boil down to the positive number operations!
 *
 * For this purpose, it might be smart to allow operations
 * exclusively over positive numbers, and let the user operate
 * negative number operations. Or just add a few ifs before the
 * actual calculations!
 */

#include "ptype.h"
#include "pcode.h"

#include <stdio.h>
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
 * return chr - '0';
 *
 * Returns 10 if the digit is wrong
 */
pusint _pbi_chr2dig ( pchr chr ) {

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
		default:  return 10;

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

/* Checks if 'bi' is set to "0" */
pbool pbi_isnull( pbi bi ) { return ( strcmp(bi, "0") == 0 ); }

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
pbool pbi_isvalid( pstr val ) {

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
			 * This applies to the ASCII values
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
pbool pbi_isneg ( pbi bi ) {

	/* Sign and at least one digit */
	if ( strlen(bi) >= 2 ) return ( bi[0] == '-' );

	/*
	 * In any other case,
	 * there's not enough space for a sign and
	 * at least one digit,
	 * so it can't be valid and negative!
	 */
	return P_FALSE;

}

pcode pbi_cmp( pbi bi1, pbi bi2 ) {

	psz l1 = strlen(bi1);
	psz l2 = strlen(bi2);
	psz cmp;

	if ( l1 > l2 ) return P_GREATER;
	if ( l1 < l2 ) return P_SMALLER;

	/*
	 * This bit below relies on the fact
	 * that the compiler is using ASCII.
	 * I *might* generalize the solution
	 * if a problem arises!
	 */

	cmp = strcmp(bi1, bi2);

	if ( cmp > 0 ) return P_GREATER;
	if ( cmp < 0 ) return P_SMALLER;
	return P_EQUAL;

}

pcode pbi_cmpN( pbi bi, P_BI_OP_TYPE val ) {

	pcode result;
	pstr val_str;
	P_BI_OP_TYPE tmp = val;
	pusint dig = 0;

	while ( tmp != 0 ) { dig++; tmp /= 10; }
	val_str = (pstr)malloc( ( dig + 1 ) * sizeof(puchr) );
	if (val_str == NULL) return P_BADALLOC;

	sprintf(val_str, "%u", val);

	result = pbi_cmp(bi, val_str);

	free(val_str);

	return result;

}

pbi pbi_add( pbi bi1, pbi bi2 ) {

	pusint carry = 0;
	psint i;
	pstr s;
	pstr ret;
	psz l, l1, l2, lbig, lsmall;
	pusint tmp;
	pstr bibig;

	l1 = strlen(bi1);
	l2 = strlen(bi2);

	/* DEBUG
	printf("l1 = %lu, l2 = %lu\n", l1, l2);
	*/

	if ( l1 > l2 ) { lbig = l1; lsmall = l2; bibig = bi1; }
	else           { lbig = l2; lsmall = l1; bibig = bi2; }

	/*
	 * The largest the new number can be is
	 * one larger than the bigger of the two numbers
	 * plus another character for the NULL terminator
	 *
	 * As an example: 99 + 99, two largest two-digit integers, result in 198
	 * Add to that a NULL terminator, and you get 4 characters!
	 */
	l = lbig + 2;

	/* DEBUG
	printf("lbig = %lu, lsmall = %lu\n", lbig, lsmall);
	*/

	s = (pstr)malloc( l * sizeof(puchr) );
	if ( s == NULL ) return NULL;

	for ( i = 1; i <= lsmall; i++ ) {

		/* DEBUG
		printf("for loop %d\n", i);
		printf("  tmp = _pbi_chr2dig( bi1[%lu] ) + _pbi_chr2dig(bi2[%lu]) + %d;\n", l1-i, l2-i, carry);
		printf("  tmp = _pbi_chr2dig( %c ) + _pbi_chr2dig( %c ) + %d;\n", bi1[l1-i], bi2[l2-i], carry);
		printf("  tmp = %c + %c + %d;\n", bi1[l1-i], bi2[l2-i], carry);
		*/

		tmp = _pbi_chr2dig( bi1[l1 - i] ) + _pbi_chr2dig( bi2[l2 - i] ) + carry;

		/* DEBUG
		 printf("  tmp = %u;\n", tmp);
		*/

		carry = tmp / 10;
		/* Remember, they're being added in reversei, you gotta flip them! */
		s[i - 1] = _pbi_dig2chr( tmp % 10 );

	}

	/*
	 * After going across the digits in the smaller number,
	 * check that there's more digits.
	 *
	 * If there aren't, just add the carry to the last slot
	 */

	for ( ; i <= lbig; i++ ) {
		tmp = _pbi_chr2dig(bibig[lbig - i]) + carry;
		s[i - 1] = _pbi_dig2chr(tmp % 10);
		carry = tmp / 10;
	}

	s[i-1] = _pbi_dig2chr(carry);
	s[i] = '\0';

	printf("%s, %d\n", s, i);

	/*
	 * 'i' now points to the last index, where '\0' should be.
	 * We'll make a new string, and add the digits in reverse order!
	 */

	ret = (pstr)malloc( (i + 1)*sizeof(pchr) );
	if ( ret == NULL ) { free(s); return NULL; }

	ret[i] = '\0';
	for ( i-- ; i >= 0 ; i-- ) ret[i] = s[lbig - i];

	free(s);
	return ret;

}

#endif
