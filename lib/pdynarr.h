#ifndef PCLIB_DYNARR
#define PCLIB_DYNARR

/*
 * pdynarr.h - A simple implementation of a dynamic array
 *
 * The implementation uses a standard optimization technique which includes
 * doubling and halving the capacity, according to the number of elements in the array
 */

/* TODO: Verify if all libraries are needed, stdio is useless */

#include "ptypes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define p_dynarr(type) struct { \
	type*  data;     /* An array of all elements */ \
	p_uint size;     /* The number of elements currently in the dynamic array */ \
	p_uint capacity; /* The number of elements that can fit in the dynamic array */ \
}

#define pDynArrInit(retArr) \
	retArr.data = NULL; \
	retArr.size = 0; \
	retArr.capacity = 0;

#define pDynArrCleanup(retArr) free(retArr.data);

#endif
