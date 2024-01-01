
/*
 * bool.c - Testing the behaviour of the Boolean type
 */

#include "../lib/ptypes.h"

#include <stdio.h>

int main() {

	printf("%d\n", p_true);  /* 1 */
	printf("%d\n", p_false); /* 0 */

	printf("%d\n", p_true == !p_false); /* 1 */

	return 0;

}

