
#define PROC_Read 0x01
#define PROC_Write 0x02
#define PROC_Exec 0x04
#define MODE_CoW 0x10

#define TYPE_Memory 0
#define TYPE_SRAM 1
#define TYPE_BIOS 2
#define TYPE_Device 3
#define TYPE_Register 4

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

unsigned char stackBuffer[256];

regions registers[] ={
  {1,0x700000,4  ,PROC_Read|PROC_Write,TYPE_Register,0,0}, //eax
  {1,0x700004,4  ,PROC_Read|PROC_Write,TYPE_Register,1,0}, //ebx
  {1,0x700008,4  ,PROC_Read|PROC_Write,TYPE_Register,2,0}, //ecx
  {1,0x70000C,4  ,PROC_Read|PROC_Write,TYPE_Register,3,0}, //edx
  {1,0x700010,4  ,PROC_Read|PROC_Write,TYPE_Register,4,0}, //esi
  {1,0x700014,4  ,PROC_Read|PROC_Write,TYPE_Register,5,0}, //edi
  {1,0x700018,4  ,PROC_Read|PROC_Write,TYPE_Register,6,0}, //ebp
  {1,0x70001C,4  ,PROC_Read|PROC_Write,TYPE_Register,7,0}, //esp
  {1,0x700020,4  ,PROC_READ           ,TYPE_Register,8,0}, //eip
  {1,0x700100,256,PROC_READ|PROC_Write,TYPE_Memory  ,0,(unsigned long long)&stackBuffer[0]} //sb
};
  
int isWithin(unsigned int addr,region* r){
 return addr>r->vAddress&&addr<(r->vAddress+r->size); 
}

extern mmt biosMMT;

extern mmt processTables[65536];

extern unsigned short* const procId;
extern bool hasLeftBios;
region* getRegion(unsigned int address){
  mmt* target;
  region* currRegion;
  if(!hasLeftBios)
    target = &biosMMT;
  else{
    target = &processTable[*procId];
    if(!target->enabled||(target->flags&FLAG_UseBIOSMap)!=0)
       target = &biosMMT;
   }
   for(int i = 0;i<sizeof(registers);i++){
     currRegion = &registers[i];
     if(isWithin(address,currRegion))
       return currRegion;
   }
  for(int i = 0;i<sizeof(target->regions);i++){
     currRegion = &(target->regions)[i];
     if(isWithin(address,currRegion))
       return currRegion;
   }
  return NULL;
}
 

