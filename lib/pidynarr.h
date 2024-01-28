#ifndef PCLIB_IDYNARR
#define PCLIB_IDYNARR

/*
 * pidynarr.h
 *
 * A special case of the dynamic array defined in pdynarr.h, which doesn't use
 * the capacity optimization technique
 *
 * ==================================================
 *
 * The incremental dynamic array struct consists of the data array and size unsigned integer value.
 *
 * The incremental dynamic array reallocates memory for each addition and subtraction.
 *
 * THE USER IS RESPONSIBLE FOR HANDLING THE MEMORY AFTER EACH OPERATION!
 * So, every time malloc or realloc is called, the user should check if the pointer isn't NULL.
 *
 * ==================================================
 *
 * Functionality:
 *
 * -------------------------
 *
 * p_idynarr(p_sint) arr1;
 * pIDynArrInit(arr1);
 *
 * Declares, defines, and initializes an incremental integer array called arr1.
 *
 * -------------------------
 *
 * pIDynArrCleanup(arr1);
 *
 * Cleans up the allocated memory of arr1.
 * Sets all the values of arr1 back to NULLs and zeros.
 * Makes arr1 reusable since it can be used again with new values.
 *
 * -------------------------
 *
 * pIDynArrAdd(arr1, 4);
 * if (arr1.data == NULL) return P_BADALLOC;
 *
 * Adds the integer constant 4 to arr1.
 * Checks that the reallocation of memory, if one was necessary, was successful.
 * If it wasn't, P_BADALLOC (from pcodes.h) is returned.
 *
 * -------------------------
 *
 * pIDynArrRemove(arr1);
 *
 * Removes the last element from arr1.
 * Checks that the reallocation of memory, if one was necessary, was successful.
 *
 * ==================================================
 *
 * Taken variables:
 *
 * pIDynArrIter
 * Used for the for-loop in pIDynArrRemove
 *
 * pIDynArrTmpPtr
 * Used for safely checking realloc successfulness
 */

#include "ptypes.h"

#include <stdlib.h> /* malloc, realloc, free */

p_uint pIDynArrIter;
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
