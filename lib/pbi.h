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
 * === DEVNOTE ===
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

/*
 * The bigint datatype
 * Essentially, a string
 */
typedef pstr pbi;

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

/* TODO: Don't forget the null terminator */
pbi pbi_add( pbi bi1, pbi bi2 ) {

	pusint carry = 0;
	psz i;

	psz l1 = strlen(bi1);
	psz l2 = strlen(bi2);
	/* +1 for the carry, +1 for the null terminator */
	psz l = l1 + l2 + 2;

	pstr s = (pstr)malloc( l * sizeof(puchr) );

}

#endif
