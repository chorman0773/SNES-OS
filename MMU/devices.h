#ifndef __devices_h_2018_05_15_15_26
#define __devices_h_2018_05_15_15_26

struct device{
  int (*read)(unsigned long long,unsigned char*,unsigned int);
  int (*write)(unsigned long long,const unsigned char*,unsigned int);
};


device* getDevice(unsigned int);

#endif
