#include "../lib/pbi.h"
#include "../lib/ptype.h"
#include "../lib/pcode.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BISIZE 20

pcode main() {

	pbi bi1[BISIZE] = "123324";
	pbi bi2[BISIZE] = "124";
	pbi bi3[BISIZE];

	_pbi_addb(bi1, bi2, bi3, BISIZE);
	printf("%s + %s = %s\n", bi1, bi2, bi3);

	_pbi_subb(bi1, bi2, bi3, BISIZE);
	printf("%s - %s = %s\n", bi1, bi2, bi3);

	return P_SUCCESS;

}
