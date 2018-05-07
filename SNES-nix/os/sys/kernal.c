#include <bios/BIOS.h>
#include <bios/SNESnix-Thread.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <bios/HDDAccess.h>


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
    char memname[16]= "";
    char outname[15]= "/proc/self/mem";
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
    __asm__ volatile("cont_:\n\tPER cont_\n\tLDK pb\n\tPHK");
    newProc.threads[currThread->threadId] = *currThread;
    newProc.threads[currThread->threadId].priority = 100000;
    __asm__ volatile("PLA");
    __asm__ volatile("CLI");
    if(currThread->reg.eax!=currProcess->pid){
        numProcesses++;
        processes[pid] = newProc;
        return newProc;
    } else{
        oldPid = currThread->reg.eax;
        currThread->priority = 0;
        strcpy(memname,"\\proc\\");
        strcat(memname,itoa(oldPid));
        strcat(memname,"\\mem");
        relink(memname,outname);
    }
}


void irqHandler()__attribute__(biosHandler("IRQ")){
    currProcess->activeThreadId++;
    __asm__ volatile("CLI");
    __asm__ volatile("RTI");
}

void brkHandler()__attribute__(biosHandler("BRK")){
    unsigned short swi;
    __asm__ volatile("STA %0":"=r"(swi));
    switch(swi){
        case 0x40:
            int code = ebx;
            
        ;
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
            
    }
    va_end(args);
    __asm__ volatile("CLI");
}
void shutdownHandler(){
    __asm__ volatile("SEI");
    
    __asm__ volatile("CLI");
}

void boot()__attribute__((noreturn)){
      void(*irq)() = irqHandler;
      void(*brk)() = brkHandler;
      void(*syscall)() = syscallHandler;
      void(*shutdown)() = shutdownHandler;
      set_syscall(syscall);
      set_brkhandler(brk);
      set_irqhandler(irq);
      set_shutdownhandler(shutdown);
      os.gid = 0;
      os.uid = 0;
      os.pid = 0;
      os.threads = calloc(sizeof(struct _thread),2);
      processes[0] = os;
      stop();
}


