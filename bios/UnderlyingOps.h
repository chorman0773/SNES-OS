#ifndef __Ops32_h_2018_06_08_13_08
#define __Ops32_h_2018_06_08_13_08
#ifdef __cplusplus
extern "C"{
#endif
/*
  __bioscall calling convention:
  All Parameters (except ... parameter of syscall) appear in snes registers or x86-like registers.
  Up to the first 3 1 or 2 byte parameters appear in A, X, and Y in that order.
  Up to the first 6 3 or 4 byte paramaters and any 1 or 2 byte parameters after the first 3 appear in
  eax, ebx, ecx, edx, esi, and edi in that order.
  __bioscall functions do not create a stack frame.
  Any functions called by __bioscall functions are done via JMP or JMP (long) (those subroutines return to the caller
    of the initial function, rather than the __bioscall function).
  All return values are put into registers. (A for 1 or 2 byte, eax for 4 byte, rax for 8 byte).
  Asside from the div32, and div64 functions (which return a value into eax and ebx or rax and rbx respectively),
  No functions return a struct type.
*/
  
  
/*
  MMU level Fast Move routines.
  eax is the primary register, so it can be moved to any register (except eip), and have any register moved to it.
  Other registers can only be moved to eax (except for esp, which can also be moved to ebp)
*/
__bioscall void moveEaxToEbx();
__bioscall void moveEaxToEcx();
__bioscall void moveEaxToEdx();
__bioscall void moveEaxToEsi();
__bioscall void moveEaxToEdi();
__bioscall void moveEaxToEbp();
__bioscall void moveEaxToEsp();
__bioscall void moveEbxToEax();
__bioscall void moveEcxToEax();
__bioscall void moveEdxToEax();
__bioscall void moveEsiToEax();
__bioscall void moveEdiToEax();
__bioscall void moveEbpToEax();
__bioscall void moveEspToEax();
__bioscall void moveEipToEax();
__bioscall void moveEspToEbp();

/*
  MMU level Fast Swap Routines
  eax can swap with every register (except eip).
  Other registers can only swap with eax.
*/
__bioscall void swapEaxAndEbx();
__bioscall void swapEaxAndEcx();
__bioscall void swapEaxAndEdx();
__bioscall void swapEaxAndEsi();
__bioscall void swapEaxAndEdi();
__bioscall void swapEaxAndEsp();
__bioscall void swapEaxAndEbp();

struct div32_result __attribute((register)){
  int quotient;
  int remainder;
};
struct div64_result __attribute((register)){
  long quotient;
  long remainder;
};

/*
  MMU level 64-bit move routines (note that rax means eax:ebx and rbx means ecx:edx)
*/
__bioscall void moveRaxToRbx();
__bioscall void moveRbxToRax();
__bioscall void swapRaxAndRbx();

__bioscall void frameEnter(unsigned short);
__bioscall void frameExit();

__bioscall int add32(int,int);
__bioscall int sub32(int,int);
__bioscall int mul32(int,int);
__bioscall struct div32_result div32(int,int);


__bioscall long add64(long,long);
__bioscall long sub64(long,long);


#ifdef __cplusplus
};
#endif
#endif
