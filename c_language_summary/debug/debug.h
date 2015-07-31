#ifdef __cplusplus
extern "C"{
#endif

#ifndef __DBG_PUB_H__
#define __DBG_PUB_H__

#include <stdio.h>
#include <syslog.h>


typedef enum {
        D_LOG_TRACE,
        D_LOG_INFO,   
        D_LOG_ERR,    
        D_LOG_CRIT,   
        D_LOG_FATAL,  
        D_LOG_NONE     
} gf_loglevel_t;

#define LOG_PRINT_LEVEL D_LOG_INFO

// 定义各个级别日志的简称 
char* LOG_NAME[] = {
      "TRACE",   
      "INFO",   
      "ERR",   
      "CRIT",  
      "FATAL",   
      "UNKNOWN", 
};

#define get_log_levname(loglevel)   (loglevel >=D_LOG_TRACE && loglevel <= D_LOG_FATAL)? LOG_NAME[loglevel]:LOG_NAME[D_LOG_NONE]

#define LOG_PRINT(tp, fmt, args...) \
do { \
    if (tp >= LOG_PRINT_LEVEL) \
    { \
         syslog(D_LOG_INFO,"[logging: %s] %s:%s():%d: " fmt "\n",  \
         get_log_levname(tp),__FILE__, __FUNCTION__, __LINE__, ##args); \
    } \
} \
while (0)


#ifdef DEBUG

#define DBG_OUT printf("%s:%d:%s: ", __FILE__, __LINE__, __FUNCTION__);fflush(stdout);
#define DBG_PRINT(fmt, arg...) DBG_OUT printf(fmt "\n", ##arg);

#else

#define DBG_OUT
#define DBG_PRINT(fmt, arg...)

#endif

#define DBG_PERROR(fmt) DBG_OUT perror(fmt "\n");



#endif

#ifdef __cplusplus
}
#endif

