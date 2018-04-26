#ifndef __BIOS_h__intern_04_17_2018_19_04
#define __BIOS_h__intern_04_17_2018_19_04

#define PROC_Read 0x0001
#define PROC_Write 0x0002
#define PROC_Exec 0x0010
#ifdef __cplusplus
#define __cdecl extern "C"
#else
#define __cdecl
#endif
#define __nativedecl __cdecl



__nativedecl void setpermissions(void*,unsigned int,unsigned short);

__nativedecl void setProtectionLevel(int);

__nativedecl void stop() __attribute__((noreturn));

__nativedecl void syscall(unsigned short);


__nativedecl void set_syscall(void(*)());

__nativedecl void set_brkhandler(void(*)());
__nativedecl void set_irqhandler(void(*)());
__nativedecl void set_shutdownhandler(void(*)());

#endif
