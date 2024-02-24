#include "../lib/pcode.h"
#include "../lib/pdict.h"
#include "../lib/ptype.h"

#include <stdio.h>

#define addNCheck(dict, k, v) \
	pdict_add(dict, k, v) \
	if ( (dict.keys == NULL) || (dict.vals == NULL) ) return P_BADALLOC;

int main() {

	int i;

	pdict(p_str, p_str) nicknames;
	pdict_init(nicknames);

	addNCheck(nicknames, (p_str)"Marcus", (p_str)"Mark");
	addNCheck(nicknames, (p_str)"Michael", (p_str)"Mike");
	addNCheck(nicknames, (p_str)"Agnes", (p_str)"Nessa");

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
