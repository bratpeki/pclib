#ifndef PCLIB_DYNARR
#define PCLIB_DYNARR

/*
 * pdynarr.h
 *
 * A simple implementation of a type-generic dynamic array
 *
 * ==================================================
 *
 * The dynamic array consists of the data array, and size and capacity integer values.
 *
 * The dynamic array uses the following optimization technique:
 *   Once the size of the dynamic array is equal to the capacity, the capacity is doubled
 *   Once the size of the dynamic array is equal to half the capacity, the capacity is halved
 *
 * THE USER IS RESPONSIBLE FOR HANDLING THE MEMORY AFTER EACH RE-EVALUATION OF THE CAPACITY!
 * So, every time malloc or realloc is called, the user should check if the pointer isn't NULL.
 *
 * ==================================================
 *
 * Usage:
 *
 * p_dynarr(p_sint) array1;
 * Creates a dynamic array called array1.
 *
 * pDynArrInit(array1);
 * Initiazes array1.
 *
 * pDynArrCleanup(array1);
 * Cleans up the allocated memory of arrayy1.
 * Sets all the values of array1 back to zeros and NULL.
 * Makes array1 reusable, since it can be initiazed again, with new values.
 *
 * pDynArrAdd(array1, 4);
 * Adds the integer constant '4' to the end of array1.
 *
 * pDynArrAdd(array1, 0);
 * Removes the integer element at index 0 from array1.
 *
 * ==================================================
 *
 * Taken variables:
 *
 * pDynArrIter
 * Used for the for-loop in pDynArrRemove
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
		arr.data = NULL; \
		arr.size = 0; \
		arr.cap = 0; \
	} while (0);

/*
 * Clears the memory of the array,
 * and set the variables back to their initial state
 */
#define pDynArrCleanup(arr) \
	do { \
		free(arr.data); \
		arr.data = NULL; \
		arr.size = 0; \
		arr.cap = 0; \
	} while (0);

/*
 * Adds the element 'el' to the dynamic array 'arr'
 * If needed, doubles the capacity of the array
 */
#define pDynArrAdd(arr, el) \
	do { \
		if ( arr.data == NULL ) { \
			arr.data = malloc(sizeof(*(arr.data))); \
			if ( arr.data != NULL ) { \
				(arr.data)[0] = el; \
				arr.size = 1; \
				arr.cap = 1; \
			} \
		} \
		else { \
			if ( arr.size == arr.cap ) { \
				arr.data = realloc(arr.data, sizeof(*(arr.data))*2); \
				if ( arr.data != NULL ) arr.cap *= 2; \
				else pDynArrCleanup(arr); \
			} \
			(arr.size)++; \
			(arr.data)[arr.size - 1] = el; \
		} \
	} while (0);

#endif

/* Removes an element at the given index from the given array */
#define pDynArrRemove(arr, index) \
	do { \
		p_uint pDynArrIter; \
		if ( (arr.data != NULL) && ((index) < arr.size) && ((index) >= 0) ) { \
			for (pDynArrIter = (index); pDynArrIter < arr.size - 1; pDynArrIter++) { \
				(arr.data)[pDynArrIter] = (arr.data)[pDynArrIter + 1]; \
			} \
			(arr.size)--; \
			if (arr.size < ((arr.cap)/2)) { \
				arr.data = realloc(arr.data, sizeof(*(arr.data)) * (arr.cap / 2)); \
				if (arr.data != NULL) { arr.cap /= 2; } \
				else pDynArrCleanup(arr); \
			} \
		} \
	} while (0);
