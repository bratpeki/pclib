#ifndef PCLIB_CODE
#define PCLIB_CODE

/*
 * pcode.h
 *
 * Exit codes for common situations
 *
 * ===============
 *
 * Each exit code is described with a comment.
 *
 * The header doesn't use:
 *
 *   typedef enum { ... } pcode
 *
 * since I wanted to enable the user to write the main function as:
 *
 *   pcode main( ... ) {
 *     ...
 *     return P_SUCCESS;
 *   }
 *
 * A typedef doesn't enable that behaviour in GCC,
 * since pcode is then a custom type, and not an int.
 */

#define pcode int

enum {

	P_SUCCESS,     /* Successful exit */

	P_BADFILE,     /* File error */
	P_BADALLOC,    /* Allocation error */
	P_BADARG,      /* A passed argument is bad */

	P_OUTOFBOUNDS, /* Array indexing error */

	P_GREATER,     /* Comparison, first is greater */
	P_SMALLER,     /* Comparison, first is smaller */
	P_EQUAL        /* Comparison, both equal */

};

#endif
