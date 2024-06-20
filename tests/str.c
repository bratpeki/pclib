
#include "../lib/pstr.h"
#include "../lib/ptype.h"
#include "../lib/pcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pcode main() {

	pchr abc[30] = "This is the first example!";
	pstr def = calloc(30, sizeof(pchr));
	pchr t1[20] = "  trim example  ";
	pchr t2[20];

	printf("%s\n", abc);
	pstr_flip(abc);
	printf("%s\n", abc);

	if ( def == NULL ) return P_BADALLOC;
	memcpy(def, "This is the second example!", 28);

	printf("%s\n", def);
	pstr_flip(def);
	printf("%s\n", def);

	pstr_trim(t1, t2, ' ', 20);
	printf("ORIGINAL: '%s'\nTRIMMED: '%s'\n", t1, t2);

	printf( "COUNT S: ababab -> aba -> %lu\n", pstr_counts("ababab", "aba"));
	printf( "COUNT C: ababab -> a -> %lu\n", pstr_countc("ababab", 'a'));

	free(def);

	return P_SUCCESS;

}
