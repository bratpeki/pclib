/*
 * bool.c - Testing the behaviour of the Boolean type
 */

#include "../lib/ptype.h"

#include <stdio.h>

int main() {

	printf("%d %d\n", P_TRUE,  P_ON);  /* 1 1 */
	printf("%d %d\n", P_FALSE, P_OFF); /* 0 0 */

	return 0;

}
