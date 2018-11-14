#ifndef __types_h_2018_06_06_12_49
#define __types_h_2018_06_06_12_49

typedef int off_t;

typedef int fd_t;

typedef unsigned short pid_t;
typedef unsigned short uid_t;
typedef unsigned short gid_t;
typedef unsigned short devno_t;

typedef void noreturn_t;

#define withc(type) const type
#define ptr(type) type*
#define cptr(type) const type*

#define withv(type) volatile type
#define withcv(type) const volatile type
#define vptr(type) volatile type*
#define cvptr(type) const volatile type*


#endif
