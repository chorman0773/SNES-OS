#include <bios/BIOS.h>
#include <bios/SNESnix-Thread.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <bios/HDDAccess.h>
#include <os/fs/path.h>
#include <os/fs/dev/setup-devfs.h>


typedef struct{
    bool active;
    int pid;
    int uid;
    int gid;
    int ctid;
    int activeThreadId;
    int threadCount;
    thread threads;
}process;
process os;
process processes[65536];
thread*  threads;
extern process* currProcess;
extern thread currThread;
unsigned int cpid = 1;
int numProcesses = 1;


process fork(int uid,int gid){
    int pid = cpid++;
    int oldPid = currProcess->pid;
    process newProc;
    int i;
    __asm__ volatile("SEI");
    newProc.pid = pid;
    newProc.uid = uid;
    newProc.gid = gid;
    newProc.ctid = currProcess->ctid;
    newProc.threadCount = currProcess->threadCount;
    newProc.threads = calloc(sizeof(struct _thread),newProc.threadCount);
    for(i = 0;i<newProc.threadCount;i++){
        newProc.threads[i] = currProcess->threads[i];
        newProc.threads[i].procId = pid;
    }
    currThread->reg.eax = oldPid;
    saveThread();
    newProc.threads[currThread->threadId] = *currThread;
    newProc.threads[currThread->threadId].priority = 100000;
    if(currThread->reg.eax!=currProcess->pid){
        numProcesses++;
        processes[pid] = newProc;
        return newProc;
    } else{
        oldPid = currThread->reg.eax;
        copyMemory(currProcess->pid,oldPid);
    }
}


void irqHandler()__attribute__(biosHandler("IRQ")){
    currProcess->activeThreadId++;
    __asm__ volatile("CLI");
    __asm__ volatile("RTI");
}

void brkHandler(unsigned short swi,...)__attribute__(biosHandler("BRK")){
    switch(swi){
        case 0x20:
            printf("Read access violation at %p",esi);
            abort();
        break;
        case 0x21:
            printf("Write access violation at %p",esi);
            abort();
        break;
        case 0x22:
            printf("Execute access violation at %p",esi);
            abort();
        break;
        case 0x40:
            int code = ebx;
            exit(code);
        break;
        case 0x41:
            abort();
        break;
    }
    
    __asm__ volatile("CLI");
    __asm__ volatile("RTI");
}

void syscallHandler(unsigned short syscall,...)__attribute__(biosHandler("syscall")){
    __asm__ volatile("SEI");
    va_list args;
    va_start(args);
    switch(syscall){
        case 0:
            const char* name = va_arg(args,const char*);
            int mode = va_arg(args,int);
        break;
    }
    va_end(args);
    __asm__ volatile("CLI");
}
void shutdownHandler(){
    __asm__ volatile("SEI");
    
    __asm__ volatile("CLI");
}

void boot(unsigned short snesBiosVersion, unsigned short mmuCoreVersion,int bootArgc,const char** bootArgv)__attribute__((noreturn)){
      void(*irq)() = irqHandler;
      void(*brk)(unsigned int,...) = brkHandler;
      void(*syscall)(unsigned short,...) = syscallHandler;
      void(*shutdown)() = shutdownHandler;
      path* devs[4];
      unsigned int(*devSources[4])(unsigned long long,unsigned char*,unsigned int);
      void (*devSinks[4])(unsigned long long,unsigned const char*,unsigned int);
      set_syscall(syscall);
      set_brkhandler(brk);
      set_irqhandler(irq);
      set_shutdownhandler(shutdown);
      os.gid = 0;
      os.uid = 0;
      os.pid = 0;
      os.threads = calloc(sizeof(struct _thread),2);
      processes[0] = os;
      initDevfs(devs,devSources,devSinks);
      stop();
}


