#ifndef __printf_h_2018_04_23_13_30
#define __printf_h_2018_04_23_13_30
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <stdarg.h>
typedef struct {
    bool isSprintf;
    char pad;
    int len;
    int decDigs;
    union{
        FILE* fp;
        char* str;
    }outputBuffer;
    va_list args;
}printf_state;

typedef void(*formatHandle)(printf_state*);


void writeChar(char c,printf_state* st);

#ifdef __cplusplus
};
#endif
#endif
