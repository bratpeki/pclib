#ifndef PCLIB_DICT
#define PCLIB_DICT

/*
 * pdict.h - A simple implementation of a type-generic dictionary/hashmap
 */

#include "ptypes.h"

#include <stdlib.h> /* malloc, realloc, free */

p_vptr pDictKeyPtr;
p_vptr pDictValPtr;

/* The dynamic array macro */
#define p_dict(ktype, vtype) struct { \
	ktype* keys; /* An array of all keys */ \
	vtype* vals; /* An array of all values */ \
	p_uint size; /* The number of elements currently in the dictionary */ \
	p_uint cap;  /* The number of elements that can fit in the dictionary */ \
}

#define pDictInit(dict) \
	do { \
		dict.keys = NULL; \
		dict.vals = NULL; \
		dict.size = 0; \
		dict.cap = 0; \
	} while (0)

#define pDictCleanup(dict) \
	do { \
		free(dict.keys); \
		free(dict.vals); \
		dict.keys = NULL; \
		dict.vals = NULL; \
		dict.size = 0; \
		dict.cap = 0; \
	} while (0);

#define pDictAdd(dict, key, val) \
	do { \
		if ( (dict.keys == NULL) || (dict.vals == NULL) ) { \
			dict.keys = malloc(sizeof(*(dict.keys))); \
			dict.vals = malloc(sizeof(*(dict.vals))); \
			if ( (dict.keys != NULL) && (dict.vals != NULL) ) { \
				(dict.keys)[0] = key; \
				(dict.vals)[0] = val; \
				dict.size = 1; \
				dict.cap = 1; \
			} \
		} \
		else { \
			if ( dict.size == dict.cap ) { \
				pDictKeyPtr = realloc(dict.keys, sizeof(*(dict.keys)) * dict.cap * 2); \
				pDictValPtr = realloc(dict.vals, sizeof(*(dict.vals)) * dict.cap * 2); \
				if ( (pDictKeyPtr != NULL) && (pDictValPtr != NULL) ) { \
					dict.cap *= 2; \
					dict.keys = pDictKeyPtr; \
					dict.vals = pDictValPtr; \
				} \
				else pDictCleanup(dict); \
			} \
			(dict.size)++; \
			(dict.keys)[dict.size - 1] = key; \
			(dict.vals)[dict.size - 1] = val; \
		} \
	} while (0);

#endif

#define pDictRemove(dict, index) \
	do { \
		p_uint pDictIter; \
		if ( (dict.size > 0) && ((index) < dict.size) && ((index) >= 0) ) { \
			for (pDictIter = (index); pDictIter < dict.size - 1; pDictIter++) { \
				(dict.keys)[pDictIter] = (dict.keys)[pDictIter + 1]; \
				(dict.vals)[pDictIter] = (dict.vals)[pDictIter + 1]; \
			} \
			(dict.size)--; \
			if (dict.size < ((dict.cap)/2)) { \
				pDictKeyPtr = realloc(dict.keys, sizeof(*(dict.keys)) * (dict.cap / 2)); \
				pDictValPtr = realloc(dict.vals, sizeof(*(dict.vals)) * (dict.cap / 2)); \
				if ( (pDictKeyPtr != NULL) && (pDictValPtr != NULL) ) { \
					dict.cap /= 2; \
					dict.keys = pDictKeyPtr; \
					dict.vals = pDictValPtr; \
				} \
				else pDictCleanup(dict); \
			} \
		} \
	} while (0);
