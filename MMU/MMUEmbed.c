




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
}entry;

typedef struct{
  char enabled;
  char flags;
  int pid;
  entry entries[1637];
  char padding[14];
  void* mmtPtr;
}mmt; 

extern mmt biosMMt;

extern mmt processTables[65536];


