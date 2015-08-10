#ifdef __cplusplus
extern "C"{
#endif

#include<stdint.h> /*定义了 uint64_t等*/
#include<stdio.h>
#include"debug.h"

int32_t main(int32_t argc, char **argv)
{
    DBG_PRINT("test debug 1 %s_%d","test",1);
    DBG_PRINT("test debug 2 %s_%d","test",2);
    LOG_PRINT(D_LOG_INFO,"test debug 1 %s_%d","test",1);
    LOG_PRINT(0,"test debug 1 %s_%d","test",1);
    LOG_PRINT(7,"test debug 1 %s_%d","test",1);
    return 0;
}

#ifdef __cplusplus
}
#endif