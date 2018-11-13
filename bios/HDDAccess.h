#ifndef __HDDAccess_h_2018_04_23_17_31
#define __HDDAccess_h_2018_04_23_17_31
#include <stddef.h>

#include "../../SNES-OS/bios/BIOS.h"

    typedef unsigned int size_t;
    __nativedecl int open(const char*,int);
    __nativedecl void close(int);
    __nativedecl void write(int,size_t,const void*,size_t);
    __nativedecl int read(int,size_t,void*,size_t);
    
    __nativedecl void unlink(const char*);
    __nativedecl void relink(const char*,const char*);
    __nativedecl const char* tmpname();

#endif
