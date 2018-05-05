#ifndef __setjmp_h_2018_04_20_12_20
#define __setjmp_h_2018_04_20_12_20

#define setjmp(buf) _setjmp(&buf);
typedef struct{
  int(*returnAddress)();
  void* bp;
  void* sp;
}jmp_buf;

int _setjmp(jmp_buf*);
void longjmp(jmp_buf,int)__attribute__((noreturn));

#endif


