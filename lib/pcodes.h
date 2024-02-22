#ifndef PCLIB_CODES
#define PCLIB_CODES

/*
 * pcodes.h
 *
 * Exit codes for common situations
 */

typedef enum {

	P_SUCCESS,     /* Successful exit */
	P_BADFILE,     /* File error */
	P_BADALLOC,    /* Allocation error */
	P_OUTOFBOUNDS, /* Array indexing error */
	P_EMPTYOUTPUT, /* The function didn't output anything */
	P_GREATER,     /* Comparison, first is greater */
	P_SMALLER,     /* Comparison, first is smaller */
	P_EQUAL        /* Comparison, both equal */

} p_codes;

#endif
