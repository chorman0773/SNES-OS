#ifndef __SNESnix_thread_h_2018_04_23_14_07
#define __SNESnix_thread_h_2018_04_23_14_07
#include <bios/BIOS.h>
typedef enum _state{
	STOPPED, STARTED, UNINITIZED, WAITING
}state;

typedef struct _thread{
	void* base;
	void* stack;
	int procId;
	int threadId;
	int priority;
	int waitTime;
	unsigned short acc;
	unsigned short x;
	unsigned short y;
	unsigned char db;
    unsigned char flags;
	state st;
}* thread;



typedef void(*threadCall)(void);

__nativedecl void threadNew(thread*);
__nativedecl void threadStart(thread,threadCall);
__nativedecl void threadWait(thread);
__nativedecl void currentThread(thread*);
__nativedecl void threadResume(thread);
__nativedecl void threadStop(thread);
__nativedecl void threadKill(thread);
__nativedecl void threadInterupt(thread);

#endif
