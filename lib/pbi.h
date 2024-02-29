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
 *     pbi_isval  DONE
 *     pbi_fs
 *     pbi_isneg  DONE
 *     pbi_cmp    DONE
 *     pbi_cmpN   DONE
 *     pbi_add    MISSING NEGATIVES
 *     pbi_addN   UNTESTED
 *     pbi_sub
 *     pbi_subN   UNTESTED
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
 * return (chr - '0');
 *
 * Returns -1 if the digit is wrong
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
 * Return 0 if the digit is out-of-range.
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

pcode pbi_fs( pbi bi ) {

	return P_SUCCESS;

}

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
 * containing the sum of the bigint and number.
 *
 * Doesn't check the validity of the bigint.
 *
 * The user is responsible for clearing the memory
 * of the returned string.
 */
pbi pbi_addN(pbi bi1, P_BI_OP_TYPE num) {

	psz len = 1; /* Gotta account for the null terminal */
	P_BI_OP_TYPE num_iter = num;
	pbi ret, bnum;

	while ( num_iter != 0 ) {
		len++;
		num_iter /= 10;
	}

	bnum = (pbi)malloc( sizeof(pchr) * len );
	if ( bnum == NULL ) return NULL;

	/*
	 * TODO: %u is for unsigned ints,
	 * so this might not be the best approach,
	 * since, the user can specify the type used
	 *
	 * Maybe force the user to use classic unsigned ints
	 */
	sprintf(bnum, "%u", num);

	ret = pbi_add(bi1, bnum);

	free(bnum);

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
			ret = "0";
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

/*
 * Returns a dynamically allocated string
 * containing the difference of the bigint and number.
 *
 * Doesn't check the validity of the bigint.
 *
 * The user is responsible for clearing the memory
 * of the returned string.
 */
pbi pbi_subN(pbi bi1, P_BI_OP_TYPE num) {

	psz len = 1; /* Gotta account for the null terminal */
	P_BI_OP_TYPE num_iter = num;
	pbi ret, bnum;

	while ( num_iter != 0 ) {
		len++;
		num_iter /= 10;
	}

	bnum = (pbi)malloc( sizeof(pchr) * len );
	if ( bnum == NULL ) return NULL;

	/*
	 * TODO: %u is for unsigned ints,
	 * so this might not be the best approach,
	 * since, the user can specify the type used
	 *
	 * Maybe force the user to use classic unsigned ints
	 */
	sprintf(bnum, "%u", num);

	ret = pbi_sub(bi1, bnum);

	free(bnum);

	return ret;

}

#endif
