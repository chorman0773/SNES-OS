#ifndef __Ops32_h_2018_06_08_13_08
#define __Ops32_h_2018_06_08_13_08
#ifdef __cplusplus
extern "C"{
#endif

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


/*
  MMU level 64-bit move routines (note that rax means eax:ebx and rbx means ecx:edx)
*/
__bioscall void moveRaxToRbx();
__bioscall void moveRbxToRax();
__bioscall void swapRaxAndRbx();

__bioscall void frameEnter(unsigned short);
__bioscall void frameExit();


#ifdef __cplusplus
};
#endif
#endif
