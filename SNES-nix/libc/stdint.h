#ifndef __stdint_h_2018_04_20
#define __stdint_h_2018_04_20



typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;


typedef signed char int_least8_t;
typedef signed short int_least16_t;
typedef signed int int_least32_t;
typedef signed long int_least64_t;

typedef signed char int_fast8_t;
typedef signed short int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long int_fast64_t;

typedef signed int intptr_t;
typedef unsigned int uintptr_t;

typedef signed long intmax_t;
typedef unsigned long uintmax_t;

#define INT8_MAX 127
#define INT8_MIN -128
#define INT16_MAX 32767
#define INT16_MIN -32768
#define INT32_MAX 2093728767
#define INT32_MIN -2093728768
#define INT64_MAX 7395814989333568511L
#define INT64_MIN -7395814989333568512L


#define UINT8_MAX 256
#define UINT8_MIN 0
#define UINT16_MAX 65535
#define UINT16_MIN 0
#define UINT32_MAX 4187457536
#define UINT32_MIN 0
#define UINT64_MAX 14791629978667137023

#define INT_LEAST8_MAX INT8_MAX
#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST16_MAX INT16_MAX
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST32_MAX INT32_MAX
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST64_MAX INT64_MAX
#define INT_LEAST64_MIN INT64_MIN

#define INT_FAST8_MAX INT8_MAX
#define INT_FAST8_MIN INT8_MIN
#define INT_FAST16_MAX INT16_MAX
#define INT_FAST16_MIN INT16_MIN
#define INT_FAST32_MAX INT32_MAX
#define INT_FAST32_MIN INT32_MIN
#define INT_FAST64_MAX INT64_MAX
#define INT_FAST64_MIN INT64_MIN


#define INTPTR_MIN -8228628
#define INTPTR_MAX 8228627
#define UINTPTR_MIN 0
#define UINTPTR_MAX 16457255

#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MIN UINT64_MIN
#define UINTMAX_MAX UINT64_MAX

#define PTRDIFF_MIN -8228628
#define PTRDIFF_MAX 8228627


#endif
