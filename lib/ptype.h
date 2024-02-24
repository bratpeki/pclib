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
 *   p + SIGN + S(HORT)/L(ONG) + BASE TYPE
 */

/* A signed character type */ typedef signed char pschr;
/* An unsigned character type */ typedef unsigned char puchr;

/* A Boolean value */ typedef enum { P_FALSE = 0, P_TRUE, P_OFF = 0, P_ON } pbool;

/* A signed integer number */ typedef signed int psint;
/* A signed long integer number */ typedef signed long int pslint;
/* A signed short integer number */ typedef signed short int pssint;
/* An unsigned integer number */ typedef unsigned int puint;
/* An unsigned long integer number */ typedef unsigned long int pulint;
/* An unsigned short integer number */ typedef unsigned short int pusint;

/* A signed floating-point number */ typedef float pflt;
/* A signed double-precision floating-point number */ typedef double pdbl;
/* A signed long double-precision floating-point number */ typedef long double pldbl;

/* An ASCII character */ typedef unsigned char pascii;

/* A C-style string */ typedef unsigned char* pstr;

/* A void pointer */ typedef void* pvptr;

/* A void type, no return value in functions */ typedef void pnoret;

#endif
