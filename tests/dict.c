#include "../lib/pcode.h"
#include "../lib/pdict.h"
#include "../lib/ptype.h"

#include <stdio.h>

/* The user is responsible for checking the allocation successfulness */
#define addNCheck(dict, k, v) \
	pdict_add(dict, k, v) \
	if ( (dict.keys == NULL) || (dict.vals == NULL) ) return P_BADALLOC;

int main() {

	int i;

	pdict(pstr, pstr) nicknames;
	pdict_init(nicknames);

	addNCheck(nicknames, (pstr)"Marcus", (pstr)"Mark");
	addNCheck(nicknames, (pstr)"Michael", (pstr)"Mike");
	addNCheck(nicknames, (pstr)"Agnes", (pstr)"Nessa");

	printf("Capacity: %u\n\n", nicknames.cap); /* 4 */

	for (i = 0; i < nicknames.size; i++)
		printf("%s : %s\n", (nicknames.keys)[i], (nicknames.vals)[i]);

	printf("\n");
	pdict_rem(nicknames, 1); /* Removes "Michael":"Mike" */

	for (i = 0; i < nicknames.size; i++)
		printf("%s : %s\n", (nicknames.keys)[i], (nicknames.vals)[i]);

	pdict_rem(nicknames, 0); /* Removes "Markus:Mark" */
	pdict_rem(nicknames, 0); /* Removes "Agnes:Nessa" */
	pdict_rem(nicknames, 0); /* Dictionary is empty */

	pdict_clean(nicknames);

	return P_SUCCESS;

}
