#ifndef PCLIB_TYPES
#define PCLIB_TYPES

/*
 * pytpes.h - The definitions of various datatypes
 */

/* === BYTE TYPES === */

/* A signed byte */ typedef signed char p_sbyte;
/* An unsigned byte */ typedef unsigned char p_ubyte;

/* === INTEGER NUMBER TYPES === */

/* A signed integer number */ typedef signed int p_sint;
/* A signed long integer number */ typedef long signed int p_lsint;
/* A signed long long integer number */ typedef long long signed int p_llsint;

/* An unsigned integer number */ typedef unsigned int p_uint;
/* An unsigned long integer number */ typedef long unsigned int p_luint;
/* An unsigned long long integer number */ typedef long long unsigned int p_lluint;

/* === FLOATING POINT NUMBER TYPES === */

/* A signed floating point number */ typedef float p_flt;
/* A signed double-precision floating point number */ typedef double p_dbl;
/* A signed double-precision floating point number */ typedef double p_lflt;
/* A signed double-precision long floating point number */ typedef long double p_llflt;
/* A signed double-precision long floating point number */ typedef long double p_ldbl;

/* === LONELY TYPES === */

/* A void pointer */ typedef void* p_vptr;

/* An ASCII character */ typedef unsigned char p_chr;
/* A C-style string */ typedef char* p_str;

/* TODO: bools */
/* TODO: remove the "TYPES" headers, level the code */

#endif
