#ifndef __BIOS_h__intern_04_17_2018_19_04
#define __BIOS_h__intern_04_17_2018_19_04

#define PROC_Read 0x0001
#define PROC_Write 0x0002
#define PROC_Exec 0x0010

#define __nativecall __attribute__((convention(bios)))

#ifndef __cplusplus
#define __nativedecl extern"C" __nativecall
#else
#define __nativedecl __nativecall
#endif

#define __bioscall __nativedecl


__nativedecl void setpermissions(void*,unsigned int,unsigned short);

__nativedecl void setProtectionLevel(int);

__nativedecl void stop() __attribute__((noreturn));

__nativedecl void syscall(unsigned short,...);


__nativedecl void set_syscall(void(*)(unsigned short,...));

__nativedecl void set_brkhandler(void(*)(unsigned short));
__nativedecl void set_irqhandler(void(*)());
__nativedecl void set_shutdownhandler(void(*)());

#endif
