#include <devices.h>

device devices[256];
unsigned char registered[256];


void registerDeviceDriver_impl(unsigned char c,device d){
  devices[c] = d;
  registered[c] = 1;
}

void unregisterDeviceDriver_impl(unsigned char c){
  registered[c] = 0;
}

void init(){
  registerDeviceDriver_impl(16,{readNull,writeNull});
  registerDeviceDriver_impl(17,{readZeros,writeZeros});
  registerDeviceDriver_impl(18,{readFull,writeFull});
  registerDeviceDriver_impl(19,{readUrandom,writeUrandom});
  registerDeviceDriver_impl(20,{readRandom,writeRandom});
}

int registerDeviceDriver(unsigned char c,device d){
  if(registered[c])
    return -1;
  else
    registerDeviceDriver_impl(c,d);
   return 0;
}

int unregisterDeviceDriver(unsigned char c){
  if(!registered[c])
    return 1;
   else switch(c){
   case 16:
   case 17:
   case 18:
   case 19:
   case 20:
    return -1;
   break;
   default:
    unregisterDeviceDriver_impl(c);
    return 0;
   break;
   }
}
