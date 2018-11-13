#ifndef __terminals_h_2018_06_05_12_30
#define __terminals_h_2018_06_05_12_30

#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>
#include "../../SNES-OS/os/types.h"

#define TERM_STDIN 0
#define TERM_STDOUT 1
#define TERM_STDERR 2


typedef struct{
  pid_t terminalPid;
  pid_t executingProcess;
  uid_t owner;
  gid_t ownerId;
  size_t nfds;
  fd_t fds[];
}terminal;

typedef ptr(terminal) pterminal;
typedef cptr(terminal) cpterminal;

typedef struct{
  const terminal* term;
  uint8_t flags;
  int writeX;
  int writeY;
  int writeColor;
  int lineLength;
  int maxLines;
}termopts;

typedef ptr(termopts) ptermopts;
typedef cptr(termopts) cptermopts;

cpterminal getOwningTerminal();

cpterminal getTerminalImage(pid_t);

void overlapTerminal(cpterminal);

pid_t newTerminalImage(const char*,int,fd_t stdfdOut[]);
  
bool isDisplaying(cpterminal);

cptermopts getOptions(cpterminal,int);
void setOptions(cpterminal,int,cptermopts);

pterminal dupTerminal(cpterminal);
  
int getch();

#ifdef __cplusplus
};
#endif
#endif
