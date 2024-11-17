#ifndef PCLIB_MAC
#define PCLIB_MAC

/*
 * pmac.h
 *
 * Useful macros
 */

#include <stddef.h> /* NULL */

/* MATH */

/* Returns the bigger number of the two */
#define PMAC_MAX2( x, y ) ( (x) >= (y) ) ? (x) : (y)
/* Returns the smaller number of the two */
#define PMAC_MIN2( x, y ) ( (x) <= (y) ) ? (x) : (y)
/* Returns if the number is between the two values, including them */
#define PMAC_BETWEEN( l, x, h ) ( (l) <= (x) ) && ( (x) <= (r) )
/* Linearly interpolates X between two points, (x0, y0) and (x1, y1), and returns Y */
#define PMAC_LININT( x0,y0, x1,y1, x ) ( (y0)*((x1)-(x))+(y1)*((x)-(x0)) ) / ((x1)-(x0))

/* ALLOCATION */

/* if ( x == NULL ) return NULL */
#define PMAC_INRN( x ) if ( (x) == NULL ) return NULL;

#endif
