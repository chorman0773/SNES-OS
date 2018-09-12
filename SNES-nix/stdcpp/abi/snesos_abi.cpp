/*
 * snesos_abi.cpp
 *
 *  Created on: Sep 11, 2018
 *      Author: connor
 */
#include <abi/snesos_abi.hpp>
#include <cstddef>

extern void*volatile* ebp [[register("ebp")]];
extern void*volatile* esp [[register("esp")]];



void* __cxa_getStackFrame(std::size_t n){
	void** frameBase = ((void**)*ebp);
	while(n-->0){
		frameBase = ((void**)*frameBase);
		if(frameBase==0)
			return 0;
	}
	return *frameBase;
}
