#include <stdio.h>
#include <stdlib.h>

void stackchkfail()__attribute((noreturn)){
  perror("STACK SMASHING DETECTED");
  abort();
}
