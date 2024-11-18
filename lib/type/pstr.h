#ifndef PCLIB_STR
#define PCLIB_STR

/*
 * pstr.h
 *
 * Various string functions
 *
 * TODO:
 * - pstr_substr(d) - Missing checks for 'a' and 'b', do I want those?
 */

#include <string.h> /* strlen, memcpy */
#include <stdlib.h> /* calloc */

/*
 * Reverse the order of the characters in 's'.
 *
 * The maximum accepted string length is the maximum value of size_t.
 *
 * Params:
 * 1. s - The input string
 *
 * Returns:
 * Nothing
 */
void pstr_flip( char* s );

/*
 * Trim the front and back of the 'in' string, storing the result in the 'out' string.
 * 'target' is the target character to trim.
 *
 * The maximum accepted string lengths are the maximum value of size_t.
 * The length of 'out' can be equal to or smaller than the length of 'in',
 * because you trim charactrers from it, but it's suggested to have them be
 * the same length.
 *
 * Params:
 * 1. in - The input string
 * 2. out - The trimmed output string
 * 3. target - The target character
 *
 * Returns:
 * Nothing
 */
void pstr_trim( char* in, char* out, char target );

/*
 * Trim the front and back of the string 'in'
 * and return a dynamically allocated trimmed string.
 * 'target' is the target character to trim.
 *
 * The maximum length of 'in' is the maximum value of size_t.
 *
 * Params:
 * 1. in - The input string
 * 2. out - The pointer to where the trimmed string will be stored
 * 3. target - The target character
 *
 * Returns:
 * The address where the string is stored, if memory allocation is successful.
 * NULL, if memory allocation is not successful.
 */
char* pstr_trimd( char* in, char target );

/*
 * Counts how many times a character appears in a string.
 * 'haystack' is the string we're looking in.
 * 'needle' is the character we're looking for.
 *
 * The maximum length of 'haystack' is the maximum value of size_t.
 *
 * Params:
 * 1. haystack - The input string
 * 2. needle - The character we're looking for
 *
 * Returns:
 * The number of occurances.
 */
size_t pstr_countc( char* haystack, char needle );

/*
 * Counts how many times a substring appears in a string.
 * 'haystack' is the string we're looking in.
 * 'needle' is the substring we're looking for.
 *
 * The maximum lengths of the strings is the maximum value of size_t.
 *
 * Params:
 * 1. haystack - The input string
 * 2. needle - The substring we're looking for
 *
 * Returns:
 * The number of occurances.
 */
size_t pstr_counts( char* haystack, char* needle );

/*
 * Get a substring from index 'a' to index 'b' in the input string 'in'
 * and store it in the output string 'out'.
 * Both indeces are included in the substring, meaning that
 * everything from 'in[a]' to 'in[b]' is captured in the substring.
 *
 * Params:
 * 1. in - The input string
 * 2. out - The substring
 * 3. a - The starting index
 * 4. b - The ending index
 *
 * Returns:
 * Nothing
 */
void pstr_substr( char* in, char* out, size_t a, size_t b );

/*
 * Get a substring from index 'a' to index 'b' in the input string 'in',
 * allocate memory for it and store it in the 'out' pointer.
 * Both indeces are included in the substring, meaning that
 * everything from 'in[a]' to 'in[b]' is captured in the substring.
 *
 * Params:
 * 1. in - The input string
 * 2. a - The starting index
 * 3. b - The ending index
 *
 * Returns:
 * The address where the substring is stored, if memory allocation is successful.
 * NULL, if memory allocation is not successful.
 */
char* pstr_substrd( char* in, size_t a, size_t b );

/* ================================================================================ */



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

void pstr_trim( char* in, char* out, char target ) {

	size_t l, r;

	l = 0;
	r = strlen(in) - 1;

	while ( in[l] == target ) l++;
	while ( in[r] == target ) r--;

	memcpy(out, in + l*sizeof(char), r-l+1);
	out[r-l+1] = '\0';

}

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

size_t pstr_countc( char* haystack, char needle ) {

	size_t count = 0, idx = 0;

	while ( haystack[idx] )
		count += ( haystack[idx++] == needle);

	return count;

}

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

void pstr_substr( char* in, char* out, size_t a, size_t b ) {

	memcpy(out, in + a, b - a + 1);
	out[b - a + 1] = '\0';

}

char* pstr_substrd( char* in, size_t a, size_t b ) {

	char* ret = (char*)calloc(b - a + 2, sizeof(char));
	if (ret == NULL) return NULL;

	memcpy(ret, in + a, b - a + 1);
	ret[b - a + 1] = '\0';

	return ret;
}

#endif