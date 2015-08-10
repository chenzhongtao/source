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


// ע��: ͷ�ļ���Ҫ�������,������������ܻ��ظ�����
// �������������־�ļ�� 
//char* LOG_NAME[] = {
//      "TRACE",   
//      "INFO",   
//      "ERR",   
//      "CRIT",  
//      "FATAL",   
//      "UNKNOWN", 
//};

//#define get_log_levname(loglevel)   (loglevel >=D_LOG_TRACE && loglevel <= D_LOG_FATAL)? LOG_NAME[loglevel]:LOG_NAME[D_LOG_NONE]
//char * get_log_levname(loglevel)
//{
//    switch(loglevel)  
//    { 
//       case D_LOG_TRACE: return "TRACE";  break;
//       case D_LOG_INFO:  return "INFO";   break;
//       case D_LOG_ERR:   return "ERR";    break;
//       case D_LOG_CRIT:  return "CRIT";   break;
//       case D_LOG_FATAL: return  "FATAL"; break;
//       default:          return  "UNKNOWN";
//    } 
//} 

    
#define LOG_PRINT(tp, fmt, args...) \
do { \
    if (tp >= LOG_PRINT_LEVEL) \
    { \
         syslog(D_LOG_INFO,"[logging: %s] %s:%s():%d: " fmt "\n",  \
         #tp,__FILE__, __FUNCTION__, __LINE__, ##args); \
    } \
} \
while (0)

/*
    extern FILE *stderr;
    close(stderr);
    stderr = fopen("/root/log","a");
    ʹ����������ض���
*/


#ifdef DEBUG

#define DBG_OUT fprintf (stderr,"%s:%d:%s: ", __FILE__, __LINE__, __FUNCTION__);
#define DBG_PRINT(fmt, arg...) DBG_OUT fprintf (stderr,fmt "\n", ##arg);

#else

#define DBG_OUT
#define DBG_PRINT(fmt, arg...)

#endif

#define DBG_PERROR(fmt) DBG_OUT perror(fmt "\n");
#define PRINT(fmt, arg...)  fprintf (stderr,fmt , ##arg);



#endif

#ifdef __cplusplus
}
#endif

