#ifndef PCLIB_TYPE
#define PCLIB_TYPE

/*
 * ptype.h
 *
 * The definitions of various datatypes
 */

#include <stdlib.h>

/* A Boolean value */ typedef enum { P_FALSE = 0, P_TRUE, P_OFF = 0, P_ON } pbool;
/* A C-style string, terminated */ typedef char* pstr;
/* Size */ typedef size_t size_t;

#endif
