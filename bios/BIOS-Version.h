#ifndef __BIOS_Version_h_2018_04_28_15_55
#define __BIOS_Version_h_2018_04_28_15_55
typedef struct{
  int major;
  int minor;
}version;

void current(version*);
void fromEncoded(version*,unsigned short);
void fromMajorMinor(version*,int,int);
void fromString(version*,const char*);
int getMajor(const version*);
int getMinor(const version*);
version getOrigin(const version*);
char* toString(const version*,char*);
#endif
