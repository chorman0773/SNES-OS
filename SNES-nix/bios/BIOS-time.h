#ifndef __BIOS_time_h_2018_04_23_12_29
#define __BIOS_time_h_2018_04_23_12_29

#include <bios/BIOS.h>

typedef struct{
    long seconds;
    int nanos;
}RTCInstant;

__nativedecl int BIOS_getFrameCount();
__nativedecl long BIOS_getRTC();
__nativedecl RTCInstant BIOS_getRTCInstant();


#endif
