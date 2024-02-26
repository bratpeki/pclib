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
 *     pbi
 *     pbi_isnull
 *     pbi_set
 *     pbi_clean
 *     pbi_isneg
 *     pbi_cmp
 *     pbi_cmpN
 *     pbi_add
 *     pbi_addN
 *     pbi_sub
 *     pbi_subN
 * - Consider multiplication and division.
 * - Also, isn't this a bigint header, then, if there are no floating points?
 * - A BIGINT IS ZERO ONLY WHEN THE SIZE OF 'dig' IS ZERO!
 *   Anything else would break the digit count checkers.
 */

#include "ptype.h"
#include "pcode.h"

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
 * The bigint
 * Essentially, a string
 */
typedef pstr pbi;

/* Checks if 'bi' is set to "0" */
pbool pbi_isnull( pbi bi ) { return (pbool)( strcmp(bi, "0") == 0 ); }

/*
 * Returns P_TRUE if 'val' is in a valid format for a bigint,
 * and P_FALSE if it isn't
 *
 * The proper format is:
 * (+, - OR A DIGIT) + (SERIES OF DIGITS) + '\0'
 */
pbool pbi_isvalid( pstr val ) {

	puint i = 0;

	/* Obviously! */
	if ( val == NULL ) return P_FALSE;

	/* An empty string isn't a bigint */
	if ( val[0] == '\0' ) return P_FALSE;

	/* Obviously! Part 2! */
	if (
		(strcmp(val, "+") == 0) ||
		(strcmp(val, "-") == 0)
	) return P_FALSE;

	if ( (val[0] == '+') || (val[0] == '-') ) i = 1;

	for ( ; val[i] != '\0'; i++ ) {

		switch ( val[i] ) {

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
 * Sets 'bi' to the literal string 'val', if it is properly formatted
 *
 * 'bi' has to point to NULL
 */
pcode pbi_set( pbi bi, pstr val ) {

	/*
	 * First, we check if 'val' is properly formatted
	 *
	 */
	if ( !pbi_isvalid(val) ) return P_BADARG;

	if ( bi != NULL ) return P_BADARG;

	strcpy(bi, val);

	return P_SUCCESS;

}

#endif
