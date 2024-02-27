#ifndef PCLIB_ARR
#define PCLIB_ARR

/*
 * parr.h
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
 * Header includes (private elements ommited):
 *   parr       strcut
 *   parr_init  function
 *   parr_clean function
 *   parr_add   function
 *   parr_rem   function
 */

#include "ptype.h"

#include <stdlib.h> /* malloc, realloc, free */

/* Used for the for-loop in parr_rem */
puint _parr_iter;

/* Used for safely checking realloc successfulness */
pvptr _parr_tmp;

/* The dynamic array macro */
#define parr(type) struct { \
	type*  data; /* An array of all elements */ \
	puint size; /* The number of elements currently in the dynamic array */ \
	puint cap;  /* The number of elements that can fit in the dynamic array */ \
}

/* Initiazes the array defined with the parr macro. */
#define parr_init(arr) \
	do { \
		(arr).data = NULL; \
		(arr).size = 0; \
		(arr).cap = 0; \
	} while (0);

/*
 * Clears the memory of the array,
 * and sets the variables back to NULLs and zeros.
 */
#define parr_clean(arr) \
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
#define parr_add(arr, el) \
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
				_parr_tmp = realloc((arr).data, sizeof(*((arr).data)) * (arr).cap * 2); \
				if ( _parr_tmp != NULL ) { (arr).cap *= 2; (arr).data = _parr_tmp; } \
				else parr_clean(arr); \
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
#define parr_rem(arr, index) \
	do { \
		if ( ((arr).data != NULL) && ((index) < (arr).size) && ((index) >= 0) ) { \
			for (_parr_iter = (index); _parr_iter < (arr).size - 1; _parr_iter++) \
				((arr).data)[_parr_iter] = ((arr).data)[_parr_iter + 1]; \
			((arr).size)--; \
			if ((arr).size <= (((arr).cap)/2)) { \
				_parr_tmp = realloc((arr).data, sizeof(*((arr).data)) * ((arr).cap / 2)); \
				if (_parr_tmp != NULL) { (arr).cap /= 2; (arr).data = _parr_tmp; } \
				else { \
					if ( (arr).cap == 1 ) (arr).data = NULL; \
					parr_clean(arr); \
				} \
			} \
		} \
	} while (0);

#endif
