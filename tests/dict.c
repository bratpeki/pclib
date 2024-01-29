#include "../lib/pcodes.h"
#include "../lib/pdict.h"
#include "../lib/ptypes.h"

#include <stdio.h>

#define dictAddAndCheck(dict, k, v) \
	pDictAdd(dict, k, v) \
	if ( (dict.keys == NULL) || (dict.vals == NULL) ) return P_BADALLOC;

int main() {

	int i;

	p_dict(p_str, p_str) nicknames;
	pDictInit(nicknames);

	pDictAdd(nicknames, (p_str)"Marcus", (p_str)"Mark");
	pDictAdd(nicknames, (p_str)"Michael", (p_str)"Mike");
	pDictAdd(nicknames, (p_str)"Agnes", (p_str)"Nessa");

	printf("Capacity: %u\n\n", nicknames.cap); /* 4 */

	for (i = 0; i < nicknames.size; i++)
		printf("%s : %s\n", (nicknames.keys)[i], (nicknames.vals)[i]);

	printf("\n");
	pDictRemove(nicknames, 1); /* Removes "Michael":"Mike" */

	for (i = 0; i < nicknames.size; i++)
		printf("%s : %s\n", (nicknames.keys)[i], (nicknames.vals)[i]);

	pDictRemove(nicknames, 0); /* Removes "Markus:Mark" */
	pDictRemove(nicknames, 0); /* Removes "Agnes:Nessa" */
	pDictRemove(nicknames, 0); /* Dictionary is empty */

	pDictCleanup(nicknames);

	return P_SUCCESS;

}
