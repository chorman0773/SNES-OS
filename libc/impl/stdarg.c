#include <stdarg.h>
#include <stdlib.h>

#include "../../SNES-OS/os/Registers.h"


void __va_start(va_list* list,void* last_arg,size_t size){
	void** bp = (void**) ebp;
	void* frameSp = *bp;
	void* frameBp = *((void**)*bp);
	void* argsList = (void*)((void**)((char*)last_arg)+size)+1);
	list->bp = frameBp;
	list->lastArg = last_arg;
	list->buff = argsList;
	list->prevArg = last_arg;
}

void __va_end(va_list* list){
	void** bp = (void**) ebp;
	*((void**)*bp) = list->buff;
	list->buff = NULL;
	list->prevArg = NULL;
}

void* __va_arg(va_list* list,int size){
	char* output = (char*) list->buff;
	list->prevArg = output;
	list->buff = output+size;
	return list->buff;
}
