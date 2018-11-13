#include "../../../SNES-OS/os/executable/snes-os-binary.h"

#include <string.h>

int loadHeader(header* head,FILE* bin){
  if(bin==NULL||ferror(bin))
    return -1;
  fread(head->magic,4,1,bin);
  if(!strncmp(head->magic,magic))
    return 1;
}
