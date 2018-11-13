/*
 * snesos_abi.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: connor
 */
#include <abi/snesos_abi.hpp>
#include <cstddef>
#include <exception>

extern void**volatile ebp [[register("ebp")]];
extern void**volatile esp [[register("esp")]];

struct __cxa_static_object_handler{
	destructor dtor;
	void* target;
	void* domain;
};
extern __cxa_static_object_handler handlers[];
std::size_t hId{0};
thread_local void** unwindSp;
thread_local void** unwindBp;
thread_local void* exception;
thread_local const std::type_info* exception_rtti;
thread_local destructor exception_dtor;

void __cxa_at_exit(destructor dtor,void* obj,void* domain){
	handlers[hId++] = {dtor,obj,domain};
}
void __cxa_finalize(void* domain){
	for(std::size_t pos=0;pos<hId;pos++)
		if(domain==0||handlers[pos].domain==domain)
			handlers[pos].dtor(handlers[pos].target);
}

void* __cxa_getStackFrame(std::size_t n){
	void** frameBase = ((void**)(*(ebp+std::ptrdiff_t(4))));
	while(n-->0){
		frameBase = ((void**)*(frameBase+std::ptrdiff_t(4)));
		if(frameBase==0)
			return 0;
	}
	return *frameBase;
}

pc_address __cxa_getCallingPc(std::size_t n){
	pc_address* frame = (pc_address*) __cxa_getStackFrame(n+1)+std::ptrdiff_t(8);
	return *frame;
}

const extended_function_info* __cxa_getExtendedFunctionInfo(std::size_t n){
	const extended_function_info** info =  (const extended_function_info**)__cxa_getStackFrame(n+1);
	return *info;
}

void __cxa_destroy(void* obj,destructor dtor){
	dtor(obj);
}
void __cxa_destroy_range(void* arr,std::size_t oSize,std::size_t len,destructor dtor){
	char* carr = (char*)arr;
	char* end = carr+(len*oSize);
	for(;carr!=end;carr+=oSize)
		__cxa_destroy(carr,dtor);
}

void __cxa_unwindEnd(pc_address addr){
	if(addr==0)
		std::terminate();//If addr is 0 it means that exception handling is being aborted, so call std::terminate
	else{
		esp = unwindSp;
		ebp = unwindBp;//Reinstate the stack frame that stack unwinding has ended in.
		*((*((void***)esp))--)=exception;//Push the exception
		*((*((const std::type_info***)esp))--)=exception_rtti;//Push the typeid of the exception
		*((*((destructor**)esp)--))=exception_dtor;//Push the destructor of the exception
		goto *addr;//longjmp to the exception handler
	}
}

void __cxa_doCatch(pc_address p,void* except,const std::type_info* except_rtti,const extended_function_info* inf,const exception_handler_table_entry* handler,destructor dtor){
	pc_address gotoAddr = handler->jumpTo;
	exception = except;
	exception_rtti = except_rtti;
	exception_dtor = dtor;
	unwindSp = unwindBp+(inf->frameAutoLength);
	for(std::size_t i=0;i<inf->frameCleanupTableLength;i++){
		const frame_cleanup_table_entry& entry = inf->frameCleanupTable[i];
		if(entry.startPc<p&&entry.endPc>p&&gotoAddr<entry.endPc)
			__cxa_destroy(*(unwindBp+entry.frameOffset),entry.dtor);//Call any destructors of autos falling out of scope with the exception handler
	}
	__cxa_unwindEnd(gotoAddr);
}

