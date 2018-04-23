#ifndef __BIOS_h__intern_04_17_2018_19_04
#define __BIOS_h__intern_04_17_2018_19_04

#define PROC_Read 0x0001
#define PROC_Write 0x0002
#define PROC_Exec 0x0010



#define NATIVECALL __attribute((visibility("internal")))
#define __nativedecl


typedef void(*call_handler)(void);

__nativedecl void setpermissions(void*,unsigned int,unsigned short)NATIVECALL;

__nativedecl void setProtectionLevel(int)NATIVECALL;

__nativedecl void stop()NATIVECALL __attribute__((noreturn));

__nativedecl void syscall(unsigned short)NATIVECALL;


__nativedecl void set_syscall(call_handler*)NATIVECALL;

__nativedecl void set_brkhandler(call_handler)NATIVECALL;
__nativedecl void set_irqhandler(call_handler)NATIVECALL;
__nativedecl void set_shutdownhandler(call_handler)NATIVECALL;

#endif
