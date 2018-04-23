#ifndef __stdarg_h_2018_04_20_12_27
#define __stdarg_h_2018_04_20_12_27

#ifdef __cplusplus
extern "C"{
#endif

#include <stddef.h>

typedef struct{
    void* last_arg;
    void* prev_arg;
    void* buff;
    void* bp;
}va_list;

#define va_start(ap,last_arg) __va_start(&ap,(&last_arg)+1)
#define va_end(ap) __va_end(&ap)
#define va_arg(ap,type) *((type*)__va_arg(&ap));

void __va_start(va_list*,void*);
void __va_end(va_list*);
void* __va_arg(va_list*);

#ifdef __cplusplus
};
#endif
#endif


