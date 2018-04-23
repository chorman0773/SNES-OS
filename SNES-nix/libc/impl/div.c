#include <stdlib.h>

div_t div(int divedend,int divisor){
    div_t ret;
    ret.quot = divedend/divisor;
    ret.rem = divedend%divisor;
    return ret;
}

ldiv_t ldiv(long divedend,long divisor){
    ldiv_t ret;
    ret.quot = divedend/divisor;
    ret.rem = divedend%divisor;
    return ret;
}
