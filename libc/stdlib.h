#ifndef __stdlib_h_2018_04_17_13_12
#define __stdlib_h_2018_04_17_13_12
#include "stddef.h"
typedef unsigned long size_t;
#ifdef __cplusplus
extern "C"{
#endif
#define RAND_MAX 2147483647
	typedef struct{
		int quotient;
		int rem;
	}div_t;
    typedef struct{
        long quotient;
        long rem;
    }ldiv_t;

	void* malloc(size_t);
	void* realloc(void*,size_t);
	void* calloc(size_t,size_t);
	void free(void*);
	
	void* memcpy(void*,const void*,size_t);
	
	int rand();
	void srand(unsigned int);
	
	div_t div(int,int);
    ldiv_t ldiv(long,long);
	
	char* getenv(const char*);
    void system(const char*);
	
	void exit(int)__attribute__((noreturn));
	void abort()__attribute__((noreturn));
	int atExit(void(*)(void));

#ifdef __cplusplus
};
#endif
#endif
