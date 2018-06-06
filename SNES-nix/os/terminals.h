#ifndef __terminals_h_2018_06_05_12_30
#define __terminals_h_2018_06_05_12_30
#ifdef __cplusplus
extern "C"{
#endif

#include <stdbool.h>
#include <os/types.h>
#include <os/gfxenv.h>

#define TERM_STDIN 0
#define TERM_STDOUT 1
#define TERM_STDERR 2

typedef struct{
  pid_t terminalPid;
  pid_t executingProcess;
  uid_t owner;
  gid_t ownerId;
  devno_t stdinDev;
  devno_t stdoutDev;
  devno_t stderrDev;
  bool hasTerminalWindow;
  GFXEnv* windowEnv;
}terminal;

typedef terminal* pterminal;
typedef const terminal* cpterminal;

typedef struct{
  const terminal* term;
  bool echoChars;
  int writeX;
  int writeY;
  int writeColor;
  int lineLength;
  int maxLines;
}termopts;

typedef termopts* ptermopts
typedef const termopts* cptermopts;

cpterminal getOwningTerminal();

cpterminal getTerminalImage(pid_t);

void overlapTerminal(cpterminal);

pid_t newTerminalImage(const char*,int,fd_t stdfdOut[]);

cptermopts getOptions(cpterminal,int);
void setOptions(cpterminal,int,cptermopts);

#ifdef __cplusplus
};
#endif
#endif
