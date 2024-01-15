#ifndef PCLIB_DYNARR
#define PCLIB_DYNARR

/*
 * pdynarr.h - A simple implementation of a dynamic array
 *
 * The implementation uses a standard optimization technique which includes
 * doubling and halving the capacity, according to the number of elements in the array
 */

#include "ptypes.h"

#include <stdlib.h> /* malloc, realloc, free */

/* The dynamic array macro */
#define p_dynarr(type) struct { \
	type*  data; /* An array of all elements */ \
	p_uint size; /* The number of elements currently in the dynamic array */ \
	p_uint cap;  /* The number of elements that can fit in the dynamic array */ \
}

/* Initiazes the array defined with the p_dynarr macro */
#define pDynArrInit(arr) \
	do { \
		(arr).data = NULL; \
		(arr).size = 0; \
		(arr).cap = 0; \
	} while (p_false);

/* Clears the memory of the array,
 * and set the variables back to their initial state
 */
#define pDynArrCleanup(arr) \
	do { \
		free(arr.data); \
		(arr).data = NULL; \
		(arr).size = 0; \
		(arr).cap = 0; \
	} while (p_false);

/*
 * Adds the element 'el' to the dynamic array 'arr'
 *
 * If needed, doubles the capacity of the array
 */
#define pDynArrAdd(arr, el) \
	do { \
		if ( arr.data == NULL ) { \
			arr.data = malloc(sizeof(*((arr).data))); \
			if ( arr.data != NULL ) { \
				(arr.data)[0] = el; \
				arr.size = 1; \
				arr.cap = 1; \
			} \
		} \
		else { \
			if ( (arr).size == (arr).cap ) { \
				arr.data = realloc((arr).data, sizeof(*((arr).data))*2); \
				if ( arr.data != NULL ) arr.cap *= 2; \
				else pDynArrCleanup(arr); \
			} \
			(arr.size)++; \
			(arr.data)[arr.size - 1] = el; \
		} \
	} while (p_false);

#endif
