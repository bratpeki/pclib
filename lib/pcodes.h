#ifndef PCLIB_CODES
#define PCLIB_CODES

/*
 * pcodes.h
 *
 * Exit codes for common situations
 */

#define P_SUCCESS     0 /* Successful exit */
#define P_BADFILE     1 /* File error */
#define P_BADALLOC    2 /* Allocation error */
#define P_OUTOFBOUNDS 3 /* Array indexing error */
#define P_EMPTYOUTPUT 4 /* The function didn't output anything */
#define P_GREATER     5 /* Comparison, first is greater */
#define P_SMALLER     6 /* Comparison, first is smaller */
#define P_EQUAL       7 /* Comparison, both equal */

#endif
