#include <stdio.h>
#include <stdlib.h>

void stackchkfail()__attribute__((noreturn)){
  perror("STACK SMASHING DETECTED");
  abort();
}
