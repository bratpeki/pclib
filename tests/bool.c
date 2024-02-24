/*
 * bool.c - Testing the behaviour of the Boolean type
 */

#include "../lib/ptype.h"

#include <stdio.h>

int main() {

	printf("%d %d\n", p_true,  p_on ); /* 1 1 */
	printf("%d %d\n", p_false, p_off); /* 0 0 */

	return 0;

}
