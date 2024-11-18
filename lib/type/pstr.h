#ifndef PCLIB_STR
#define PCLIB_STR

/*
 * pstr.h
 *
 * Various string functions
 */

#include <string.h> /* strlen, memcpy */
#include <stdlib.h> /* calloc */

void pstr_flip( char* s );
void pstr_trim( char* in, char* out, char target );
char* pstr_trimd( char* in, char target );
size_t pstr_countc( char* haystack, char needle );
size_t pstr_counts( char* haystack, char* needle );

/*
 * Reverse the order of the characters in 's'
 */
void pstr_flip( char* s ) {

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
 * Ensure both arrays are the same length
 * "target" is the target character to trim
 */
void pstr_trim( char* in, char* out, char target ) {

	size_t l, r;

	l = 0;
	r = strlen(in) - 1;

	while ( in[l] == target ) l++;
	while ( in[r] == target ) r--;

	memcpy(out, in + l*sizeof(char), r-l+1);
	out[r-l+1] = '\0';

}

/*
 * Trim the string "in" and return a dynamically allocated string
 * "target" is the target character to trim
 *
 * Returns NULL if the memory cannot be allocated
 */
char* pstr_trimd( char* in, char target ) {

	size_t l, r;
	char* ret;

	l = 0;
	r = strlen(in) - 1;

	while ( in[l] == target ) l++;
	while ( in[r] == target ) r--;

	ret = (char*)calloc(r-l+2, sizeof(char));
	if ( ret == NULL ) return NULL;

	memcpy(ret, in + l*sizeof(char), r-l+1);
	ret[r-l+1] = '\0';

	return ret;

}

/*
 * Counts how many times a character appears in a string
 */
size_t pstr_countc( char* haystack, char needle ) {

	size_t count = 0, idx = 0;

	while ( haystack[idx] )
		count += ( haystack[idx++] == needle);

	return count;

}

/*
 * Counts how many times a substring appears in a string
 * Accounts for overlaps
 */
size_t pstr_counts( char* haystack, char* needle ) {

	size_t count = 0, lenh = strlen(haystack), lenn = strlen(needle);
	size_t i, j;
	int verify;

	for ( i = 0; i <= lenh-lenn; i++ ) {

		verify = 1;
		for ( j = 0; verify && (j < lenn); j++ )
			verify = ( haystack[i+j] == needle[j] );
		count += verify;

	}

	return count;

}

#endif