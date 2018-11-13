#include "../../../../SNES-OS/os/fs/dev/zeros_and_null.h"

#include <string.h>

#include "../../../../SNES-OS/os/fs/path.h"

void writeNull(unsigned long long i1, unsigned const char* i2,unsigned int i3){}

int readNull(unsigned long long i1, unsigned char* i2,unsigned int i3){
	return -1;
}

int readZeros(unsigned long long i1,unsigned char* buff,unsigned int size){
	memset(buff,0,size);
	return size;
}

