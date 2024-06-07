
#include "../lib/pstr.h"
#include "../lib/ptype.h"
#include "../lib/pcode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pcode main() {

	pchr abc[30] = "This is the first example!";
	pstr def = calloc(30, sizeof(pchr));

	printf("%s\n", abc);
	pstr_flip(abc);
	printf("%s\n", abc);

	if ( def == NULL ) return P_BADALLOC;
	memcpy(def, "This is the second example!", 28);

	printf("%s\n", def);
	pstr_flip(def);
	printf("%s\n", def);

	free(def);

	return P_SUCCESS;

}
