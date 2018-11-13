#ifndef __time_h_2018_04_20_13_05
#define __time_h_2018_04_20_13_05
#ifdef __cplusplus
extern "C"{
#endif
#include <stddef.h>

#define CLOCKS_PER_SECOND 60

struct tm {
   int tm_sec;         /* seconds,  range 0 to 59          */
   int tm_min;         /* minutes, range 0 to 59           */
   int tm_hour;        /* hours, range 0 to 23             */
   int tm_mday;        /* day of the month, range 1 to 31  */
   int tm_mon;         /* month, range 0 to 11             */
   int tm_year;        /* The number of years since 1900   */
   int tm_wday;        /* day of the week, range 0 to 6    */
   int tm_yday;        /* day in the year, range 0 to 365  */
   int tm_isdst;       /* daylight saving time             */
};

typedef unsigned int clock_t;

typedef long long time_t;

double difftime(time_t,time_t);

time_t time(time_t*);
clock_t clock();
time_t mktime(struct tm*);

struct tm* gmtime(time_t,struct tm*);
struct tm* localtime(time_t,struct tm*);

#ifdef __cplusplus
};
#endif
#endif
