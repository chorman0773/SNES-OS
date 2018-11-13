#include <setjmp.h>
#include <os/Registers.h>

int _setjmp(jmp_buf* buffer){
  eax = 0;
  buffer->sp = esp;
  buffer->bp = ebp;
  updateJmpSp(buffer);
  return eax;
} 

void updateJmpSp(jmp_buf* buffer){
  short s;
  __asm__ volatile("TSA");
  __asm__ volatile("STA %0",s);
  buffer->s = s;
}

void longjmp(jmp_buf buff,int val){
  eax = val;
  __asm__ volatile("LDA %0",buff.s);
  __asm__ volatile("TAS");
  esp = buffer->sp;
  ebp = buffer->bp;
}
