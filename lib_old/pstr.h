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

/*
 * Reverse the order of the characters in 's'
 */
void pstr_flip( pstr s ) {

	char c;
	size_t i = 0;
	size_t ss = strlen(s) - 1;

	while ( i <= ss/2 ) {

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
void pstr_trim( pstr in, pstr out, char target, size_t len ) {

	size_t l, r;

	l = r = 0;

	while ( in[r] != '\0' ) r++;
	r--;

	while ( in[l] == target ) l++;
	while ( in[r] == target ) r--;

	memcpy(out, in + l*sizeof(char), r-l+1);
	out[r-l+2] = '\0';

}

/*
 * Trim the string "in" and return a dynamically allocated string
 * "target" is the target character to trim
 *
 * Returns NULL if the memory cannot be allocated
 */
pstr pstr_trimd( pstr in, char target ) {

	size_t l, r;
	pstr ret;

	l = 0;
	r = strlen(in);

	while ( in[l] == target ) l++;
	while ( in[r] == target ) r--;

	ret = (pstr)calloc(r-l+1, sizeof(char));
	if ( ret == NULL ) return NULL;

	memcpy(ret, in + l*sizeof(char), r-l);
	ret[r+1] = '\0';

	return NULL;

}

/*
 * Counts how many times a character appears in a string
 */
size_t pstr_countc( pstr haystack, char needle ) {

	size_t count = 0, idx = 0;

	while ( haystack[idx] )
		count += ( haystack[idx++] == needle);

	return count;

}

/*
 * Counts how many times a substring appears in a string
 * Accounts for overlaps
 */
size_t pstr_counts( pstr haystack, pstr needle ) {

	size_t count = 0, lenh = strlen(haystack), lenn = strlen(needle);
	size_t i, j;
	pbool verify;

	for ( i = 0; i < lenh-lenn; i++ ) {

		verify = P_TRUE;
		for ( j = 0; verify && (j < lenn); j++ )
			verify = (pbool)(haystack[i+j] == needle[j]);
		count += verify;

	}

	return count;

}

#endif
