#ifdef __cplusplus
extern "C"{
#endif

#ifndef __COUNT_TIME_H__
#define __COUNT_TIME_H__

#include <stdio.h>
#include<time.h>
#include<sys/time.h>

     
clock_t start, end;
double cpu_time_used;

struct timeval tv_begin, tv_end;
     
#define TIME_START  gettimeofday(&tv_begin, NULL);

#define TIME_END gettimeofday(&tv_end, NULL);


     
#define TIME_END_PRINT(fmt, args...) \
do { \
     gettimeofday(&tv_end, NULL);\
     printf(fmt , ##args); \
     double end_d = tv_end.tv_sec + tv_end.tv_usec / 1000000.0;\
	 double begin_d = tv_begin.tv_sec + tv_begin.tv_usec / 1000000.0;\
     printf(",use time :%f\n" , end_d - begin_d ); \
} \
while (0)

#define CPU_TIME_START start = clock();

#define CPU_TIME_END end = clock();


     
#define CPU_TIME_END_PRINT(fmt, args...) \
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

