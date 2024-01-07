#ifndef PCLIB_DYNARR
#define PCLIB_DYNARR

/*
 * pdynarr.h - A simple implementation of a dynamic array
 *
 * The implementation uses a standard optimization technique which includes
 * doubling and halving the capacity, according to the number of elements in the array
 */

#include "ptypes.h"

typedef struct {

	p_uint sizeElem; /* Size of a single element */
	p_vptr data;     /* An array of all elements */

	p_uint size;     /* The number of elements currently in the dynamic array */
	p_uint capacity; /* The number of elements that can fit in the dynamic array */

} p_dynarr;

#endif
