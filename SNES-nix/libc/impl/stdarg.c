#include <stdarg.h>
#include <stdlib.h>


void __va_start(va_list* list,void* last_arg,size_t size){
	void** bp = (void**) 0x700018;
	void** sp = (void**) 0x70001C;
	void* frameSp = *bp;
	void* frameBp = *((void**)*bp);
	void* argsList = *((void**)((char*)last_arg)+size));
	list->bp = frameBp;
	list->lastArg = last_arg;
	list->buff = argsList;
	list->prevArg = last_arg;
}

void __va_end(va_list* list){
	list->buff = NULL;
	list->prevArg = NULL;
}

void* __va_arg(va_list* list,int size){
	char* output = (char*) list->buff;
	list->prevArg = output;
	list->buff = output+size;
	return list->buff;
}
