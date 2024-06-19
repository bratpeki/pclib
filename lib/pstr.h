#ifndef PCLIB_STR
#define PCLIB_STR

/*
 * pstr.h
 *
 * Various string functions
 */

#include "ptype.h"

#include <string.h> /* strlen, memcpy */
#include <stdlib.h> /* calloc */
#include <stdio.h> /* TODO */

/*
 * Reverse the order of the characters in 's'
 */
pnoret pstr_flip( pstr s ) {

	pchr c;
	psz i = 0;
	psz ss = strlen(s) - 1;

	while ( i < ss/2 ) {

		c = s[i];
		s[i] = s[ss-i];
		s[ss-i] = c;

		i++;

	}

}

/*
 * Trim the string "in", storing the result in the string "out"
 * "target" is the target character to trim
 * "len" is the length of BOTH of the string arrays
 */
pnoret pstr_trim( pstr in, pstr out, pchr target, psz len ) {

	psz l, r;

	l = r = 0;

	while ( in[r] != '\0' ) r++;
	r--;

	while ( in[l] == target ) l++;
	while ( in[r] == target ) r--;

	memcpy(out, in + l*sizeof(pchr), r-l+1);
	out[r-l+2] = '\0';

}

/*
 * Trim the string "in" and return a dynamically allocated string
 * "target" is the target character to trim
 *
 * Returns NULL if the memory cannot be allocated
 */
pstr pstr_trimd( pstr in, pchr target ) {

	psz l, r;
	pstr ret;

	l = 0;
	r = strlen(in);

	while ( in[l] == target ) l++;
	while ( in[r] == target ) r--;

	ret = (pstr)calloc(r-l+1, sizeof(pchr));
	if ( ret == NULL ) return NULL;

	memcpy(ret, in + l*sizeof(pchr), r-l);
	ret[r+1] = '\0';

	return NULL;

}

/*
 * Counts how many times a character appears in a string
 */
psz pstr_countc( pstr haystack, pchr needle ) {

	psz count = 0;
	psz idx = 0;

	while ( haystack[idx] )
		count += ( haystack[idx] == needle);

	return count;

}

/*
 * Counts how many times a substring appears in a string
 * TODO
 */
psz pstr_counts( pstr haystack, pchr needle ) {

	psz count = 0;

	return count;

}

#endif
