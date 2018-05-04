#ifndef __Registers_h_2018_05_04_16_38
#define __Registers_h_2018_05_04_16_38

#define eax *((int  *)0x700000)
#define ebx *((int  *)0x700004)
#define ecx *((int  *)0x700008)
#define edx *((int  *)0x70000C)

#define esi *((void**)0x700010)
#define edi *((void**)0x700014)

#define ebp *((void**)0x700018)
#define esp *((void**)0x70001C)

#endif
