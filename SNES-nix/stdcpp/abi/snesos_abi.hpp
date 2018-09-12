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

extern"C"{
/**
 * Throws the specified exception in the current stack frame.
 * \param (pc_address) exceptionStartPoint the pc in the current stack frame
 * \param (const std::type_info*) exceptionTypeId the static type of the throw exception
 * \param (void*) exception a pointer to the temporary exception object
 * \param (destructor) dtor the destructor for the exception object
 * This function will never return, even if there is a valid catch handler in the current frame
 */
__attribute__((noreturn,requires_standalone_frame)) void __cxa_throwException(pc_address,const std::type_info*,void*,destructor);
/**
 * Called when an exception leaves the current stack frame
 * May result in std::terminate being called if the current stack frame is noexcept
 * \param (pc_address) unwind point the point in the current stack frame that is being unwound from (to locate appropriate destructors)
 * \param (const void*) the exception object being thrown
 * \param (std::size_t) the frame offset. UB if this is nonzero, and it is not being called from an abi function. (1 is used by __cxa_throwException and is not UB)
 * \param (pc_address) the address of the calling function
 * This function does not return unless called from __cxa_throwException
 */
void __cxa_doUnwind(pc_address,const void*,std::size_t,pc_address);
/**
 * Called when an exception is caught to jump to the handler
 * \param (pc_address) the target of the jump to for the handler
 * \param (void*) the exception object being caught
 * \param (const std::type_info*) the typeid of the exception
 * \param (const exception_handler_table_entry*) the handler for the exception
 * \param (destructor) the destructor to call for the exception object
 */
__attribute__((noreturn)) void __cxa_doCatch(pc_address,void*,const std::type_info*,const exception_handler_table_entry*,destructor);
/**
 * Called when stack unwinding ends for any reason
 * \param (pc_address) target the address which the unwinding ended at. 0 if unwinding ends because it reached the end of the stack or a noexcept specification is violated
 */
void __cxa_unwindEnd(pc_address);
/**
 * Called to destroy a single object
 * \param (void*) object the pointer to the object to destroy
 * \param (destructor) the destructor to call
 */
void __cxa_destroy(void*,destructor);
/**
 * Destroys a range of objects starting from a given address
 * \param (void*) the start of the range
 * \param (std::size_t) the size of each object
 * \param (std::size_t) the number of elements in the range
 * \param (destructor) the destructor to call
 */
void __cxa_destroy_range(void*,std::size_t,std::size_t,destructor);
/**
 * Obtains the address of the given stack frame or the current stack frame if no arguments are given
 */
void* __cxa_getStackFrame(std::size_t=0);
/**
 * Obtains the extended function info table of the function at the given stack frame or the current frame if no arguments are given
 */
const extended_function_info* __cxa_getExtendedFunctionInfo(std::size_t=0);
/**
 * Obtains the address that the given frame will return into (when that frame is reinstated), or the
 * current pc of the calling function if no paramaters are passed
 */
pc_address __cxa_getCallingPc(std::size_t=0);
/**
 * Registers a given static destructor to be called at exit.
 * \param (destructor) the destructor to call
 * \param (void*) the object to destroy
 * \param (void*) the Domain of the handler, which may be the load-point of a shared object file, or NULL
 */
void __cxa_atexit(destructor,void*,void*);
/**
 * Finalizes all static objects in the given Domain
 */
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
};

#endif /* __SNES_OS_MASTER_SNES_NIX_STDCPP_ABI_SNESOS_ABI_HPP__2018_09_10_16_51 */
