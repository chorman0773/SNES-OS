#ifndef __stdlib_h_2018_04_17_13_12
#define __stdlib_h_2018_04_17_13_12
#include "stddef.h"
#include <bios/UnderlyingOps.h>
typedef unsigned long size_t;
#ifdef __cplusplus
extern "C"{
#endif
#define RAND_MAX 2147483647
	typedef struct div32_result div_t;
	typedef struct div64_result ldiv_t;

	void* malloc(size_t);
	void* realloc(void*,size_t);
	void* calloc(size_t,size_t);
	void free(void*);
	
	void* memcpy(void*,const void*,size_t);
	
	int rand();
	void srand(unsigned int);
	
#define div(x,y) div32(x,y)
#define ldiv(x,y) div64(x,y)
	
	char* getenv(const char*);
    void system(const char*);
	
	void exit(int)__attribute__((noreturn));
	void abort()__attribute__((noreturn));
	int atExit(void(*)(void));

#ifdef __cplusplus
};
#endif
#endif
