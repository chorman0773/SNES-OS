
#define PROC_Read 0x01
#define PROC_Write 0x02
#define PROC_Exec 0x04
#define MODE_CoW 0x10

#define TYPE_Memory 0
#define TYPE_SRAM 1
#define TYPE_BIOS 2

#define DEV_Null 16
#define DEV_Zeros 17
#define DEV_Full 18
#define DEV_Random 19
#define DEV_URandom 20

#define FLAG_WX 0x80
#define FLAG_UseBIOSMap 0x01

typedef struct{
  char enabled;
  unsigned int vAddress;
  unsigned int size;
  char permissions;
  unsigned char type;
  unsigned char devNo;
  union{
    unsigned int mirrorAddr;
    unsigned long long addr;
  }absAddress;
}region;

typedef struct{
  char enabled;
  char flags;
  int pid;
  region regions[1637];
  char padding[14];
  void* mmtPtr;
}mmt; 

extern mmt biosMMT;

extern mmt processTables[65536];

extern unsigned short* const procId;
extern bool hasLeftBios;
region* checkAccess(unsigned int address){
  mmt* target;
  if(!hasLeftBios)
    target = &biosMMT;
  else{
    target = &processTable[*procId];
    if(!target->enabled||(target->flags&FLAG_UseBIOSMap)!=0)
       target = &biosMMT;
   }
}
 

