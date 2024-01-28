#ifndef PCLIB_IDYNARR
#define PCLIB_IDYNARR

/*
 * pidynarr.h
 *
 * A special case of the dynamic array defined in pdynarr.h, which doesn't use
 * the capacity optimization technique
 *
 * The incremental dynamic array struct consists of the data array and size unsigned integer value.
 *
 * The incremental dynamic array reallocates memory for each addition and subtraction.
 *
 * THE USER IS RESPONSIBLE FOR HANDLING THE MEMORY AFTER EACH OPERATION!
 * So, every time malloc or realloc is called, the user should check if the pointer isn't NULL.
 */

#include "ptypes.h"

#include <stdlib.h> /* malloc, realloc, free */

/* Used for the for-loop in pIDynArrRemove */
p_uint pIDynArrIter;

/* Used for safely checking realloc successfulness */
p_vptr pIDynArrTmpPtr;

/* The incremental dynamic array macro */
#define p_idynarr(type) struct { \
	type*  data; /* An array of all elements */ \
	p_uint size; /* The number of elements currently in the incremental dynamic array */ \
}

/* Initializes the array defined with the p_idynarr macro. */
#define pIDynArrInit(arr) \
	do { \
		arr.data = NULL; \
		arr.size = 0; \
	} while (0);

/*
 * Clears the memory of the array,
 * and sets the variables back to NULLs and zeros.
 */
#define pIDynArrCleanup(arr) \
	do { \
		free(arr.data); \
		arr.data = NULL; \
		arr.size = 0; \
	} while (0);

/*
 * Adds the element 'el' to the incremental dynamic array 'arr'.
 * Reallocates memory for each addition.
 */
#define pIDynArrAdd(arr, el) \
	do { \
		pIDynArrTmpPtr = realloc(arr.data, sizeof(*(arr.data)) * (arr.size + 1)); \
		if (pIDynArrTmpPtr != NULL) { \
			arr.data = pIDynArrTmpPtr; \
			(arr.data)[arr.size] = el; \
			(arr.size)++; \
		} \
		else pIDynArrCleanup(arr); \
	} while (0);

/*
 * Removes an element at the given index from the incremental dynamic array 'arr'.
 * Reallocates memory for each removal.
 */
#define pIDynArrRemove(arr, index) \
	do { \
		if (arr.size > 0 && index >= 0 && index < arr.size) { \
			for (pIDynArrIter = index; pIDynArrIter < arr.size - 1; pIDynArrIter++) { \
				(arr.data)[pIDynArrIter] = (arr.data)[pIDynArrIter + 1]; \
			} \
			pIDynArrTmpPtr = realloc(arr.data, sizeof(*(arr.data)) * (arr.size - 1)); \
			if (pIDynArrTmpPtr != NULL) { arr.data = pIDynArrTmpPtr; (arr.size)--; } \
			else pIDynArrCleanup(arr); \
		} \
	} while (0);

#endif
