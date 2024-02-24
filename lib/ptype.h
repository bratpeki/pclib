#ifndef PCLIB_TYPE
#define PCLIB_TYPE

/*
 * ptype.h - The definitions of various datatypes
 *
 * Contains:
 * - character types (chr)
 * - booleans (bool)
 * - integer numbers (int)
 * - floating point numbers (flt, dbl)
 * - ASCII characters (ascii)
 * - strings (str)
 * - pointers (ptr)
 * - void (noret)
 *
 * The order in which the types are named is:
 *   p_ + SIGN + S(HORT)/L(ONG) + BASE TYPE
 */

/* A signed character type */ typedef signed char p_schr;
/* An unsigned character type */ typedef unsigned char p_uchr;

/* A Boolean value */ typedef enum { p_false = 0, p_true, p_off = 0, p_on } p_bool;

/* A signed integer number */ typedef signed int p_sint;
/* A signed long integer number */ typedef signed long int p_slint;
/* A signed short integer number */ typedef signed short int p_ssint;
/* An unsigned integer number */ typedef unsigned int p_uint;
/* An unsigned long integer number */ typedef unsigned long int p_ulint;
/* An unsigned short integer number */ typedef unsigned short int p_usint;

/* A signed floating-point number */ typedef float p_flt;
/* A signed double-precision floating-point number */ typedef double p_dbl;
/* A signed long double-precision floating-point number */ typedef long double p_ldbl;

/* An ASCII character */ typedef unsigned char p_ascii;

/* A C-style string */ typedef unsigned char* p_str;

/* A void pointer */ typedef void* p_vptr;

/* A void type, no return value in functions */ typedef void p_noret;

#endif
