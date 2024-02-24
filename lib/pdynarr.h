#ifndef PCLIB_DYNARR
#define PCLIB_DYNARR

/*
 * pdynarr.h
 *
 * A simple implementation of a type-generic dynamic array
 *
 * The dynamic array struct consists of the data array, and size and capacity unsigned
 * integer values.
 *
 * The dynamic array uses the following optimization technique:
 *   Once the size of the dynamic array is equal to the capacity, the capacity is doubled
 *   Once the size of the dynamic array is equal to half the capacity, the capacity is halved
 *
 * THE USER IS RESPONSIBLE FOR HANDLING THE MEMORY AFTER EACH RE-EVALUATION OF THE CAPACITY!
 * So, every time malloc or realloc is called, the user should check if the pointer isn't NULL.
 *
 * Taken variables:
 *
 * pDynArrIter
 *
 * pDynArrTmpPtr
 */

#include "ptypes.h"

#include <stdlib.h> /* malloc, realloc, free */

/* Used for the for-loop in pDynArrRemove */
p_uint pDynArrIter;

/* Used for safely checking realloc successfulness */
p_vptr pDynArrTmpPtr;

/* The dynamic array macro */
#define p_dynarr(type) struct { \
	type*  data; /* An array of all elements */ \
	p_uint size; /* The number of elements currently in the dynamic array */ \
	p_uint cap;  /* The number of elements that can fit in the dynamic array */ \
}

/* Initiazes the array defined with the p_dynarr macro. */
#define pDynArrInit(arr) \
	do { \
		(arr).data = NULL; \
		(arr).size = 0; \
		(arr).cap = 0; \
	} while (0);

/*
 * Clears the memory of the array,
 * and sets the variables back to NULLs and zeros.
 */
#define pDynArrCleanup(arr) \
	do { \
		free((arr).data); \
		(arr).data = NULL; \
		(arr).size = 0; \
		(arr).cap = 0; \
	} while (0);

/*
 * Adds the element 'el' to the end of the dynamic array 'arr'.
 * If needed, doubles the capacity of the array.
 */
#define pDynArrAdd(arr, el) \
	do { \
		if ( (arr).data == NULL ) { \
			(arr).data = malloc(sizeof(*((arr).data))); \
			if ( (arr).data != NULL ) { \
				((arr).data)[0] = el; \
				(arr).size = 1; \
				(arr).cap = 1; \
			} \
		} \
		else { \
			if ( (arr).size == (arr).cap ) { \
				pDynArrTmpPtr = realloc((arr).data, sizeof(*((arr).data)) * (arr).cap * 2); \
				if ( pDynArrTmpPtr != NULL ) { (arr).cap *= 2; (arr).data = pDynArrTmpPtr; } \
				else pDynArrCleanup(arr); \
			} \
			((arr).size)++; \
			((arr).data)[(arr).size - 1] = el; \
		} \
	} while (0);

/*
 * Removes an element at the given index from the given array.
 * If needed, halves the capacity of the array.
 * If the index is not right, nothing is done.
 */
#define pDynArrRemove(arr, index) \
	do { \
		if ( ((arr).data != NULL) && ((index) < (arr).size) && ((index) >= 0) ) { \
			for (pDynArrIter = (index); pDynArrIter < (arr).size - 1; pDynArrIter++) \
				((arr).data)[pDynArrIter] = ((arr).data)[pDynArrIter + 1]; \
			((arr).size)--; \
			if ((arr).size <= (((arr).cap)/2)) { \
				pDynArrTmpPtr = realloc((arr).data, sizeof(*((arr).data)) * ((arr).cap / 2)); \
				if (pDynArrTmpPtr != NULL) { (arr).cap /= 2; (arr).data = pDynArrTmpPtr; } \
				else { \
					if ( (arr).cap == 1 ) (arr).data = NULL; \
					pDynArrCleanup(arr); \
				} \
			} \
		} \
	} while (0);

#endif
