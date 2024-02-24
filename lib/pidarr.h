#ifndef PCLIB_IDARR
#define PCLIB_IDARR

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

#include "ptype.h"

#include <stdlib.h> /* malloc, realloc, free */

/* Used for the for-loop in pidarr_rem */
puint _pidarr_iter;

/* Used for safely checking realloc successfulness */
pvptr _pidarr_tmp;

/* The incremental dynamic array macro */
#define pidarr(type) struct { \
	type*  data; /* An array of all elements */ \
	puint size; /* The number of elements currently in the incremental dynamic array */ \
}

/* Initializes the array defined with the p_idynarr macro. */
#define pidarr_init(arr) \
	do { \
		(arr).data = NULL; \
		(arr).size = 0; \
	} while (0);

/*
 * Clears the memory of the array,
 * and sets the variables back to NULLs and zeros.
 */
#define pidarr_clean(arr) \
	do { \
		free((arr).data); \
		(arr).data = NULL; \
		(arr).size = 0; \
	} while (0);

/*
 * Adds the element 'el' to the incremental dynamic array 'arr'.
 * Reallocates memory for each addition.
 */
#define pidarr_add(arr, el) \
	do { \
		_pidarr_tmp = realloc((arr).data, sizeof(*((arr).data)) * ((arr).size + 1)); \
		if (_pidarr_tmp != NULL) { \
			(arr).data = _pidarr_tmp; \
			((arr).data)[(arr).size] = el; \
			((arr).size)++; \
		} \
		else pidarr_clean(arr); \
	} while (0);

/*
 * Removes an element at the given index from the incremental dynamic array 'arr'.
 * Reallocates memory for each removal.
 * If the index is not right, nothing is done.
 */
#define pidarr_rem(arr, index) \
	do { \
		if ((arr).size > 0 && index < (arr).size) { \
			for (_pidarr_iter = index; _pidarr_iter < (arr).size - 1; _pidarr_iter++) \
				((arr).data)[_pidarr_iter] = ((arr).data)[_pidarr_iter + 1]; \
			_pidarr_tmp = realloc((arr).data, sizeof(*((arr).data)) * ((arr).size - 1)); \
			if (_pidarr_tmp != NULL) { (arr).data = _pidarr_tmp; ((arr).size)--; } \
			else { \
				if ( (arr).size == 1 ) (arr).data = NULL; \
				pidarr_clean(arr); \
			} \
		} \
	} while (0);

#endif
