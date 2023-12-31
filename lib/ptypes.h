#ifndef PCLIB_TYPES
#define PCLIB_TYPES

/*
 * pytpes.h - The definitions of various datatypes
 */

/* A signed byte */ typedef signed char p_sbyte;
/* An unsigned byte */ typedef unsigned char p_ubyte;

/* A signed integer number */ typedef signed int p_sint;
/* A signed long integer number */ typedef long signed int p_lsint;

/* An unsigned integer number */ typedef unsigned int p_uint;
/* An unsigned long integer number */ typedef long unsigned int p_luint;

/* A signed floating point number */ typedef float p_flt;
/* A signed double-precision floating point number */ typedef double p_dbl;
/* A signed double-precision floating point number */ typedef double p_lflt;
/* A signed double-precision long floating point number */ typedef long double p_llflt;
/* A signed double-precision long floating point number */ typedef long double p_ldbl;

/* A void pointer */ typedef void* p_vptr;

/* An ASCII character */ typedef unsigned char p_chr;
/* A C-style string */ typedef char* p_str;

/* A Boolean value */ typedef enum { p_false, p_true } p_bool;

#endif
