#ifdef __cplusplus
extern "C"{
#endif

#ifndef __COUNT_TIME_H__
#define __COUNT_TIME_H__

#include <stdio.h>
#include <time.h>

     
clock_t start, end;
double cpu_time_used;
     
#define TIME_START start = clock();

#define TIME_END end = clock();


     
#define TIME_END_PRINT(fmt, args...) \
do { \
     TIME_END end = clock();\
     printf(fmt , ##args); \
     printf(",use time :%f\n" , ((double) (end - start)) / CLOCKS_PER_SEC ); \
} \
while (0)


#endif

#ifdef __cplusplus
}
#endif

