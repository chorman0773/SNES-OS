#include <stdlib.h>
#include <stdint.h>
uint64_t seed = ((204876688654037L) ^ 0x5DEECE66DL) & ((1L << 48) - 1);

int rand(){
    seed = (seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
    return (int)(seed>>16);
}

void srand(unsigned int s){
    seed = ((s*204876688654037L) ^ 0x5DEECE66DL) & ((1L << 48) - 1);
}
 
