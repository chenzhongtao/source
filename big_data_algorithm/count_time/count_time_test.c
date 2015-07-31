#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include <unistd.h>
#include "count_time.h"


int32_t main(int32_t argc, char **argv)
{
    TIME_START;
    sleep(2);
    TIME_END_PRINT("fun1");
    return 0;
}

#ifdef __cplusplus
}
#endif