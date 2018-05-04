#include <stdlib.h>
#include <stdint.h>
uint64_t seed;

int rand(){
    seed = (seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
    return (int)(rand()>>16);
}

void srand(unsigned int s){
    seed = ((s*4280675513) ^ 0x5DEECE66DL) & ((1L << 48) - 1);
}
 
