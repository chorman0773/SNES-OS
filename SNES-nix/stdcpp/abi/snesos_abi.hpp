/*
 * snesos_abi.hpp
 *
 *  Created on: Sep 10, 2018
 *      Author: connor
 */

#ifndef __SNES_OS_MASTER_SNES_NIX_STDCPP_ABI_SNESOS_ABI_HPP__2018_09_10_16_51
#define __SNES_OS_MASTER_SNES_NIX_STDCPP_ABI_SNESOS_ABI_HPP__2018_09_10_16_51
#include <typeinfo>
#include <cstddef>

typedef void* pc_address;
typedef void(*thiscall)(void*)__attribute__((thiscall));
typedef void(*thiscallconst)(const void*)__attribute__((thiscall));
typedef void(*thiscallvolatile)(volatile void*)__attribute__((thiscall));
typedef void(*thiscallcv)(const volatile void*)__attribute__((thiscall));
typedef thiscall destructor;
struct exception_handler_table_entry{
	const std::type_info* discriminator;
	pc_address startPc;
	pc_address endPc;
	pc_address jumpTo;
}__attribute__((packed));
struct frame_cleanup_table_entry{
	pc_address startPc;
	pc_address endPc;
	destructor dtor;
	std::ptrdiff_t frameOffset;
}__attribute__((packed));
struct extended_function_info{
	const exception_handler_table_entry* exceptionHandlerTable;
	std::size_t exceptionHandlerTableLength;
	const frame_cleanup_table_entry* frameCleanupTable;
	std::size_t frameCleanupTableLength;
	const char* name;
	bool noexceptSpecification;
}__attribute__((packed));

__attribute__((noreturn,requires_standalone_frame)) void __cxa_throwException(pc_address,const std::type_info*,void*,destructor);
void __cxa_doUnwind(pc_address,const void*,std::size_t,pc_address);
__attribute__((noreturn)) void __cxa_doCatch(pc_address,void*,const std::type_info*,const exception_handler_table_entry*,destructor);
void __cxa_unwindEnd(pc_address);
void __cxa_destroy(void*,destructor);
void __cxa_destroy_range(void*,std::size_t,std::size_t,destructor);
void* __cxa_getStackFrame(std::size_t=0);
const extended_function_info* __cxa_getExtendedFunctionInfo(std::size_t=0);
pc_address __cxa_getCallingPc(std::size_t=0);
void __cxa_atexit(destructor,void*,void*);
void __cxa_finalize(void*);
thiscall __cxa_vfget(void*,std::ptrdiff_t,std::ptrdiff_t);
thiscallconst __cxa_vfget(const void*,std::ptrdiff_t,std::ptrdiff_t);
thiscallvolatile __cxa_vfget(volatile void*,std::ptrdiff_t,std::ptrdiff_t);
thiscallcv __cxa_vfget(const volatile void*,std::ptrdiff_t,std::ptrdiff_t);
void* __cxa_dynamic_cast(void*,const std::type_info*,std::ptrdiff_t);
const void* __cxa_dynamic_cast(const void*,const std::type_info*,std::ptrdiff_t);
volatile void* __cxa_dynamic_cast(volatile void*,const std::type_info*,std::ptrdiff_t);
const volatile void* __cxa_dynamic_cast(const volatile void*,const std::type_info*,std::ptrdiff_t);
const std::type_info* __cxa_typeid(const void*,std::ptrdiff_t);


#endif /* __SNES_OS_MASTER_SNES_NIX_STDCPP_ABI_SNESOS_ABI_HPP__2018_09_10_16_51 */
