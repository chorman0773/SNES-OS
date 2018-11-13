#ifndef __stddef_h_2018_04_17_13_11
#define __stddef_h_2018_04_17_13_11

#pragma macros import("__offsetof",type,field) define("__offsetof",type,field)

#define NULL 0

#define offsetof(type,field) __offsetof(type,field)
#ifndef __cplusplus
typedef __typeof__(sizeof(int)) size_t;
#else
typedef decltype(sizeof(int)) size_t;
#endif
#endif
