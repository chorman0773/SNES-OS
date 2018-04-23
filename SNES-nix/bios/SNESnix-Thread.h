
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
	state st;
}* thread;


extern thread activeThreads[];

typedef void(*threadCall)(void);

void threadNew(thread*);
void threadStart(thread,threadCall);
void threadWait(thread);
void currentThread(thread*);
void threadResume(thread);
void threadStop(thread);
void threadKill(thread);
void threadInterupt(thread);
