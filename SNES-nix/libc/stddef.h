#ifndef __stddef_h_2018_04_17_13_11
#define __stddef_h_2018_04_17_13_11
#ifdef __cplusplus
#define NULL nullptr
#else
#define NULL 0
#endif
#define offsetof(type,field) (size_t) &(((type)NULL)->field);

typedef unsigned int size_t;

#endif
