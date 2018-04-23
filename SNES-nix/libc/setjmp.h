#ifndef __setjmp_h_2018_04_20_12_20
#define __setjmp_h_2018_04_20_12_20

#define setjmp(buf) _setjmp(&buf);

typedef int(*jmp_buf)();

int _setjmp(jmp_buf*);
void longjmp(jmp_buf,int)__attribute__((noreturn));

#endif


