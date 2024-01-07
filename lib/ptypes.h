#ifndef PCLIB_TYPES
#define PCLIB_TYPES

/*
 * pytpes.h - The definitions of various datatypes
 *
 * The order the segments, written with their abbreviation, is:
 * - character types (chr)
 * - booleans (bool)
 * - integer numbers (int)
 * - floating point numbers (flt, dbl)
 * - ASCII characters (ascii)
 * - strings (str)
 * - pointers (ptr)
 *
 * The order in which the types are named is:
 *   p_ + SIGN + LONG VARIANT + BASE TYPE
 *
 * All floating-point numbers are signed, so it's not included.
 */

/* A signed character type */ typedef signed char p_schr;
/* An unsigned character type */ typedef unsigned char p_uchr;

/* A Boolean value */ typedef enum { p_false = 0, p_true, p_off = 0, p_on } p_bool;

/* A signed integer number */ typedef signed int p_sint;
/* A signed long integer number */ typedef signed long int p_slint;
/* An unsigned integer number */ typedef unsigned int p_uint;
/* An unsigned long integer number */ typedef unsigned long int p_ulint;

/* A signed floating-point number */ typedef float p_flt;
/* A signed double-precision floating-point number */ typedef double p_dbl;
/* A signed double-precision floating-point number */ typedef double p_lflt;
/* A signed long double-precision floating-point number */ typedef long double p_llflt;
/* A signed long double-precision floating-point number */ typedef long double p_ldbl;

/* An ASCII character */ typedef unsigned char p_ascii;

/* A C-style string */ typedef unsigned char* p_str;

/* A void pointer */ typedef void* p_vptr;

#endif
