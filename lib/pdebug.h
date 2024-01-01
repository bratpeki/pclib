#ifndef PCLIB_DEBUG
#define PCLIB_DEBUG

#include "./ptypes.h"

#include <stdio.h>

p_bool pDebugToggle = p_false;

#define pDebugPrintf(x) if(pDebugToggle)printf(x)
#define pDebugSet(x) pDebugToggle = x

#endif
