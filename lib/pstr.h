#ifndef PCLIB_STR
#define PCLIB_STR

/*
 * pstr.h
 *
 * Various string functions
 */

#include "ptype.h"

#include <string.h> /* strlen */

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

#endif
