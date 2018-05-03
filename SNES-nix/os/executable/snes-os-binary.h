#ifndef __snes_os_exec_h_2018_05_02_23_00
#define __snes_os_exec_h_2018_05_02_23_00
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
const char magic[4] = "\x7fELF";
typedef struct{
  unsigned short nameLen;
  char* name;
  unsigned long fpos;
  void* addr;
  unsigned int length;
  char permissions;
}section;

typedef struct{
  unsigned short nameLen;
  char* name;
  char  unlinked;
  void* addr;
}symbol;

typedef struct{
  unsigned char mdId;
  unsigned short length;
  char* data;
}fileMd;

typedef struct{
  unsigned char mdId;
  unsigned short length;
  unsigned short symbol;
  char* data;
 }symbolMd;
 
 typedef struct{
    char magic[4];
    unsigned short nSections;
    unsigned short nSymbols;
    section* sections;
    symbol* symbols;
    void* entryPoint;
    unsigned short nMetadata;
    fileMd* metadata;
    unsigned short nSymbolMetadata;
    symbolMd* symbolMetadata;
 }header;
 
int openBinary(header*,FILE*);

int canExecute(header*);
int canDynLink(header*);

int loadBinary(header*,FILE*);

void link(FILE*,FILE*,FILE*);
  
    

#ifdef __cplusplus
};
#endif
#endif
