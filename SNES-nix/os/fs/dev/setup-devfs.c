#include "setup-devfs.h"
#include <os/fs/path.h>
#include "random.h"
#include "zeros_and_null.h"
int readRandom(unsigned long long i1,unsigned char* buff,unsigned int len){
	random(buff,len);
}
int readUrandom(unsigned long long i1,unsigned char* buff,unsigned int len){
	urandom(buff,len);
}
void setupDevfs(path** paths,int(**sources)(unsigned long long,unsigned char*,unsigned int),void(**sinks)(unsigned long long,unsigned const char*,unsigned int)){
	paths[0] = getAbsolutePath("/dev/null");
	sources[0] = readNull;
	sinks[0] = writeNull;
	paths[1] = getAbsolutePath("/dev/zeros");
	sources[1] = readZeros;
	sinks[1] = writeNull;
	paths[2] = getAbsolutePath("/dev/random");
	sources[2] = readRandom;
	sinks[2] = writeNull;
	paths[3] = getAbsolutePath("/dev/urandom");
	sources[3] = readUrandom;
	sinks[3] = writeNull;
	seedUrandom();
}
