#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include <pthread.h>
#include "mem_pool.h"
#include "../count_time/count_time.h"

#define size  5000
#define thread_num 1

struct _test_mem_t {
        char a[10240];
};
struct _test_mem_2_t {
        char a[1022];
};
struct _test_mem_3_t {
        char a[1023];
};
typedef struct _test_mem_t test_mem_t;
typedef struct _test_mem_2_t test_mem_2_t;
typedef struct _test_mem_3_t test_mem_3_t;

struct mem_pool *test_mem_pool;


void *test_fun(void *arg)
{
    int j;
    int i;
    int size_t = size/thread_num;
    printf("fun 1 size %d \n",size_t);
    test_mem_t ** mem_array   = CALLOC(size_t,sizeof(test_mem_t * )); 
    for(j=0; j<10000; j++){    
            if (!test_mem_pool)
            {
                DBG_PRINT("create mem pool error");
                return 0;
            }
        for(i=0; i<size_t; i++)
        {
            mem_array[i] = (test_mem_t *)mem_get(test_mem_pool);
        }

        for(i=0; i<size_t; i++)
        {
            mem_put(mem_array[i]) ;
        }

        
    }
    return 0;
}
void *test_fun2(void *arg)
{
    int j;
    int i;
    int size_t = size/thread_num;
    printf("fun 2 size %d \n",size_t);
    test_mem_t ** mem_array   = CALLOC(size_t,sizeof(test_mem_t * )); 
    for(j=0; j<10000; j++){
        for(i=0; i<size_t; i++)
            mem_array[i] = (test_mem_t *)MALLOC(sizeof(test_mem_t));
        for(i=0; i<size_t; i++)
            free (mem_array[i]);
    }
    return 0;
}

int32_t main(int32_t argc, char **argv)
{
      

    gf_mem_init_mempool_list();

    CPU_TIME_START;
    TIME_START;
    test_mem_pool = mem_pool_new (test_mem_t, size);
    CPU_TIME_END_PRINT("mem pool");
    TIME_END_PRINT("mem pool");
    CPU_TIME_START;
    TIME_START;

    pthread_t id[thread_num];
    int i = 0;

    for(i=0;i<thread_num;++i){
            pthread_create(&id[i],NULL,test_fun2,NULL);
    }

    for(i=0;i<thread_num;++i){
            pthread_join(id[i],NULL);
    }

    CPU_TIME_END_PRINT("mem pool");
    TIME_END_PRINT("mem pool");
    mem_pool_destroy(test_mem_pool);

    //getchar();
    return 0;
}

#ifdef __cplusplus
}
#endif
