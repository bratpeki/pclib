#ifndef PCLIB_TYPES
#define PCLIB_TYPES

/*
 * pytpes.h - The definitions of various datatypes
 *
 * The order the segments, written with their abbreviation, is:
 * - bytes (byte)
 * - booleans (bool)
 * - integer numbers (int)
 * - floating point numbers (flt, dbl)
 * - characters (chr)
 * - strings (str)
 * - pointers (ptr)
 *
 * The order in which the types are named is:
 *   p_ + l(ong) + s(igned)/u(nsigned) + base type abbreviation
 */

/* A signed byte */ typedef signed char p_sbyte;
/* An unsigned byte */ typedef unsigned char p_ubyte;

/* A Boolean value */ typedef enum { p_false = 0, p_true, p_off = 0, p_on } p_bool;

/* A signed integer number */ typedef signed int p_sint;
/* A signed long integer number */ typedef signed long int p_slint;
/* An unsigned integer number */ typedef unsigned int p_uint;
/* An unsigned long integer number */ typedef unsigned long int p_ulint;

/* A signed floating point number */ typedef float p_flt;
/* A signed double-precision floating point number */ typedef double p_dbl;
/* A signed double-precision floating point number */ typedef double p_lflt;
/* A signed long double-precision floating point number */ typedef long double p_llflt;
/* A signed long double-precision floating point number */ typedef long double p_ldbl;

/* An ASCII character */ typedef unsigned char p_chr;

/* A C-style string */ typedef unsigned char* p_str;

/* A void pointer */ typedef void* p_vptr;

#endif
