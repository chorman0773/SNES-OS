#include <stdio.h>
#include <printf.h>

const char digits[] = {'0','1','2','3','4','5','6','7','8','9'};
const char lowerHexDigits[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
const char upperHexDigits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


void writeChar(char c,printf_state* st){
    if(st->isSprintf){
        *st->outputBuffer.str = c;
        st->outputBuffer.str++;
    }else
        fwrite(&c,1,1,st->outputBuffer.fp);
}

void handleFmtFmt(printf_state* st){
    writeChar('%',st);
}







