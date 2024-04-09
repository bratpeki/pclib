#ifndef PCLIB_IARR
#define PCLIB_IARR

/*
 * piarr.h
 *
 * A special case of the dynamic array defined in pdarr.h, which doesn't use
 * the capacity optimization technique, instead incrementing the size each time the array
 * is changed
 *
 * ===============
 *
 * The incremental dynamic array struct consists of:
 * - the data array and
 * - the size of the array
 *
 * ===============
 *
 * !!! THE USER IS RESPONSIBLE FOR HANDLING THE MEMORY AFTER EACH RE-EVALUATION OF THE CAPACITY !!!
 *
 * So, after every addition or removal, the user should check
 * that the data pointer in the array struct isn't NULL.
 *
 * ===============
 *
 * Header includes (private elements ommited):
 *   piarr       struct
 *   piarr_init  function
 *   piarr_clean function
 *   piarr_add   function
 *   piarr_rem   function
 */

#include "ptype.h"

#include <stdlib.h> /* malloc, realloc, free */

/* Used for the for-loop in piarr_rem */
puint _piarr_iter;

/* Used for safely checking realloc successfulness */
pvptr _piarr_tmp;

/* The incremental dynamic array macro */
#define piarr(type) struct { \
	type* data; /* An array of all elements */ \
	puint size; /* The number of elements currently in the incremental dynamic array */ \
}

/* Initializes the array defined with the piarr macro. */
#define piarr_init(arr) \
	do { \
		(arr).data = NULL; \
		(arr).size = 0; \
	} while (0);

/*
 * Clears the memory of the array,
 * and sets the variables back to NULLs and zeros.
 */
#define piarr_clean(arr) \
	do { \
		free((arr).data); \
		(arr).data = NULL; \
		(arr).size = 0; \
	} while (0);

/*
 * Adds the element 'el' to the incremental dynamic array 'arr'.
 * Reallocates memory for each addition.
 */
#define piarr_add(arr, el) \
	do { \
		_piarr_tmp = realloc((arr).data, sizeof(*((arr).data)) * ((arr).size + 1)); \
		if (_piarr_tmp != NULL) { \
			(arr).data = _piarr_tmp; \
			((arr).data)[(arr).size] = el; \
			((arr).size)++; \
		} \
		else piarr_clean(arr); \
	} while (0);

/*
 * Removes an element at the given index from the incremental dynamic array 'arr'.
 * Reallocates memory for each removal.
 * If the index is not right, nothing is done.
 */
#define piarr_rem(arr, index) \
	do { \
		if ((arr).size > 0 && index < (arr).size) { \
			for (_piarr_iter = index; _piarr_iter < (arr).size - 1; _piarr_iter++) \
				((arr).data)[_piarr_iter] = ((arr).data)[_piarr_iter + 1]; \
			_piarr_tmp = realloc((arr).data, sizeof(*((arr).data)) * ((arr).size - 1)); \
			if (_piarr_tmp != NULL) { (arr).data = _piarr_tmp; ((arr).size)--; } \
			else { \
				if ( (arr).size == 1 ) (arr).data = NULL; \
				piarr_clean(arr); \
			} \
		} \
	} while (0);

#endif
