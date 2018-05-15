#ifndef __devices_h_2018_05_15_15_26
#define __devices_h_2018_05_15_15_26

struct device{
  int (*read)(unsigned long long,unsigned char*,unsigned int);
  int (*write)(unsigned long long,const unsigned char*,unsigned int);
};


device* getDevice(unsigned int);

void init();

int readUrandom(unsigned long long,unsigned char*,unsigned int);
int readRandom(unsigned long long,unsigned char*,unsigned int);

int writeUrandom(unsigned long long,const unsigned char*,unsigned int);
int writeRandom(unsigned long long,const unsigned char*,unsigned int);

int readNull(unsigned long long,unsigned char*,unsigned int);
int writeNull(unsigned long long,const unsigned char*,unsigned int);

int readZeros(unsigned long long,unsigned char*,unsigned int);
int writeZeros(unsigned long long,const unsigned char*,unsigned int);

int readFull(unsigned long long,unsigned char*,unsigned int);
int writeFull(unsigned long long,const unsigned char*,unsigned int);

int readAnalog(unsigned long long,unsigned char*,unsigned int);
int writeAnalog(unsigned long long,const unsigned char*,unsigned int);

#endif
