#ifndef PCLIB_DICT
#define PCLIB_DICT

/*
 * pdict.h
 *
 * A simple implementation of a type-generic dictionary/hashmap
 *
 * The dictionary struct contains the arrays for keys and values,
 * the size of the dictionary and its capacity
 *
 * The dictonary uses the following optimization technique:
 *   Once the size of the dictonary is equal to the capacity, the capacity is doubled
 *   Once the size of the dictonary is equal to half the capacity, the capacity is halved
 *
 * THE USER IS RESPONSIBLE FOR HANDLING THE MEMORY AFTER EACH RE-EVALUATION OF THE CAPACITY!
 * So, every time malloc or realloc is called, the user should check if the pointer isn't NULL.
 */

#include "ptype.h"

#include <stdlib.h> /* malloc, realloc, free */

/* Used for the for-loop in pdict_rem */
p_uint _pdict_iter;

/* Used for safely checking realloc successfulness */
p_vptr _pdict_kp, _pdict_vp;

/* The dictonary macro */
#define pdict(ktype, vtype) struct { \
	ktype* keys; /* An array of all keys */ \
	vtype* vals; /* An array of all values */ \
	p_uint size; /* The number of elements currently in the dictionary */ \
	p_uint cap;  /* The number of elements that can fit in the dictionary */ \
}

/* Initiazes the array defined with the pdict macro. */
#define pdict_init(dict) \
	do { \
		(dict).keys = NULL; \
		(dict).vals = NULL; \
		(dict).size = 0; \
		(dict).cap = 0; \
	} while (0)

/*
 * Clears the memory of the array,
 * and sets the variables back to NULLs and zeros.
 */
#define pdict_clean(dict) \
	do { \
		free((dict).keys); \
		free((dict).vals); \
		(dict).keys = NULL; \
		(dict).vals = NULL; \
		(dict).size = 0; \
		(dict).cap = 0; \
	} while (0);

/*
 * Adds the pair (key, val) to the end of the dictionary 'dict'.
 * If needed, doubles the capacity of the dictionary.
 */
#define pdict_add(dict, key, val) \
	do { \
		if ( ((dict).keys == NULL) || ((dict).vals == NULL) ) { \
			(dict).keys = malloc(sizeof(*((dict).keys))); \
			(dict).vals = malloc(sizeof(*((dict).vals))); \
			if ( ((dict).keys != NULL) && ((dict).vals != NULL) ) { \
				((dict).keys)[0] = key; \
				((dict).vals)[0] = val; \
				(dict).size = 1; \
				(dict).cap = 1; \
			} \
		} \
		else { \
			if ( (dict).size == (dict).cap ) { \
				_pdict_kp = realloc((dict).keys, sizeof(*((dict).keys)) * (dict).cap * 2); \
				_pdict_vp = realloc((dict).vals, sizeof(*((dict).vals)) * (dict).cap * 2); \
				if ( (_pdict_kp != NULL) && (_pdict_vp != NULL) ) { \
					(dict).cap *= 2; \
					(dict).keys = _pdict_kp; \
					(dict).vals = _pdict_vp; \
				} \
				else pdict_clean(dict); \
			} \
			((dict).size)++; \
			((dict).keys)[(dict).size - 1] = key; \
			((dict).vals)[(dict).size - 1] = val; \
		} \
	} while (0);

/*
 * Removes a pair at the given index from the given dictionary.
 * If needed, halves the capacity of the dictionary.
 * If the index is not right, nothing is done.
 */
#define pdict_rem(dict, index) \
	do { \
		if ( ((dict).size > 0) && ((index) < (dict).size) && ((index) >= 0) ) { \
			for (_pdict_iter = (index); _pdict_iter < (dict).size - 1; _pdict_iter++) { \
				((dict).keys)[_pdict_iter] = ((dict).keys)[_pdict_iter + 1]; \
				((dict).vals)[_pdict_iter] = ((dict).vals)[_pdict_iter + 1]; \
			} \
			((dict).size)--; \
			if ((dict).size < (((dict).cap)/2)) { \
				_pdict_kp = realloc((dict).keys, sizeof(*((dict).keys)) * ((dict).cap / 2)); \
				_pdict_vp = realloc((dict).vals, sizeof(*((dict).vals)) * ((dict).cap / 2)); \
				if ( (_pdict_kp != NULL) && (_pdict_vp != NULL) ) { \
					(dict).cap /= 2; \
					(dict).keys = _pdict_kp; \
					(dict).vals = _pdict_vp; \
				} \
				else { \
					if ( (dict).size == 0 ) { (dict).keys = (dict).vals = NULL; } \
					pdict_clean(dict); \
				} \
			} \
		} \
	} while (0);

#endif
