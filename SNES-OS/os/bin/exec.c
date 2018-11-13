#include <os/terminal.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../../SNES-OS/os/syscalls.h"


void printHelp(const char* pname){
  printf("Usage: %s [-D|--detach] [-A|--asynchronous] <program name> args\n",pname);
  puts("\tExecutes a program with the specified arguments.");
  printf("Usage: %s help\n",pname);
  puts("\tDisplays this help message");
  puts("\n");
  puts("Options:");
  puts("-D|--detach: Executes the program detached from the console executing the program");
  puts("-A|--asynchronous: Runs the program in asynchronous mode. Similar to deatched mode but async will open a new terminal image for the process.");
  
}

void deatchAsync(){
 fd_t descriptors[3];
 pid_t termPid;
 detach();
 termPid = mkTerminalImg("/bin/sh",getUid(),getGid(),descriptors());
 dup2(descriptors[0],FD_STDIN);
 dup2(descriptors[1],FD_STDOUT);
 dup2(descriptors[2],FD_STDERR);
}


int main(int argc,const char** argv,const char* envp[]){
  const char flags[] = {'D','A'};
  const char flagDesc = '-';
  const char* optDesc = "--";
  const char* const options[] = {"detach","asynchronous"};
  const char* helpStr = "help";
  const char* prgName = argv[0];
  int affectedOpt;
  const char* arg
  int i;
  bool detach = false, async = false;
  if(argc==1){
     printHelp(argv[0]);
     return 1;
  }
  if(strcmp(argv[1],helpStr)==0){
    printHelp(argv[0]);
    return 0;
  }
  for(;**argv;argv++){
    arg = *argv;
    if(arg[0]=='-'){
      if(arg[1]=='-'){
        const char* opt = arg+2;
        for(i = 0;i<2;i++)
          if(strcmp(options[i],opt)==0){
            affectedOpt = i;
            goto apply_opt;
          }
      }
      for(int i = 0;i<2;i++)
        if(arg[1]==flags[i]){
          affectedOpt = i;
          goto apply_opt;
      }
      printHelp(argv[0]);
      return 1;
      apply_opt:
      if(affectedOpt==0)
        deatch = true;
      else if(affectedOpt==1)
        async = true;
    }else{
      if(async)
        deatchAsync();
      else if(detached)
        deatch();
      return execve(arg,argc+1,envp);
    }
  }
  printHelp(helpStr);
  return 1;
}
