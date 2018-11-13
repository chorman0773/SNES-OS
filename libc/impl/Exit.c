#include <stdlib.h>

#include "../../SNES-OS/bios/BIOS.h"
#include "../../SNES-OS/os/Registers.h"

int atExit(void(*handler)(int)){
	syscall(6,handler);
	return eax;
}

void exit(int code){
	ebx = code;
	__ASM__ volatile("LDA 0x40");
	__ASM__ volatile("BRK");
}

void abort(){
	__ASM__ volatile("LDA 0x41");
	__ASM__ volatile("BRK");
}
