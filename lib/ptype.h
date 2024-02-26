#ifndef PCLIB_TYPE
#define PCLIB_TYPE

/*
 * ptype.h
 *
 * The definitions of various datatypes
 *
 * The order in which the types are named is:
 *   p + SIGN + S(HORT)/L(ONG) + BASE TYPE
 */

#include <stdlib.h>

/* A Boolean value */ typedef enum { P_FALSE = 0, P_TRUE, P_OFF = 0, P_ON } pbool;

/* A C-style string */ typedef unsigned char* pstr;
/* An ASCII character */ typedef unsigned char pascii;

/* A signed character type */ typedef signed char pschr;
/* A signed double-precision floating-point number */ typedef double pdbl;
/* A signed floating-point number */ typedef float pflt;
/* A signed integer number */ typedef signed int psint;
/* A signed long double-precision floating-point number */ typedef long double pldbl;
/* A signed long integer number */ typedef signed long int pslint;
/* A signed short integer number */ typedef signed short int pssint;

/* An unsigned character type */ typedef unsigned char puchr;
/* An unsigned integer number */ typedef unsigned int puint;
/* An unsigned long integer number */ typedef unsigned long int pulint;
/* An unsigned short integer number */ typedef unsigned short int pusint;

/* A void pointer */ typedef void* pvptr;
/* A void type, no return value in functions */ typedef void pnoret;

/* Size */ typedef size_t psz;

#endif
