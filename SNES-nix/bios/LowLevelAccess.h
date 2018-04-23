#ifndef __LowLevelAccess_h_2018_04_17_13_27
#define __LowLevelAccess_h_2018_04_17_13_27

#include "BIOS.h"

__nativedecl int getAccessMode()NATIVECALL;
__nativedecl void checkAccess(int)NATIVECALL;




#endif
