#ifndef __signal_h_2018_04_20_11_49
#define __signal_h_2018_04_20_11_49
#include <stddef.h>
#ifdef __cplusplus
extern "C"{
#endif
typedef unsigned short sig_atomic_t;
    
#define SIGABRT 0
#define SIGFPE 32
#define SIGILL 33
#define SIGINT 13
#define SIGSEGV 16
#define SIGTERM 34
#define SIGREADV 17
#define SIGWRITEV 18
#define SIGEXECV 19

void _Shandle_none(int);

#define SIG_DEF NULL
#define SIG_NONE _Shandle_none

int signal(void (*)(int));

void raise(int);

#ifdef __cplusplus
};
#endif
    
#endif
