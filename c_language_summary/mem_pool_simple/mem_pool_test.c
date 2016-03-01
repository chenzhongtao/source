#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include <pthread.h>
#include "mem_pool.h"
#include "../count_time/count_time.h"

#define size  5000
#define thread_num 10


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
    int size_t = size/thread_num+1;
    printf("fun 1 size %d \n",size_t);
    test_mem_t ** mem_array   = CALLOC(size_t,sizeof(test_mem_t * )); 
    for(j=0; j<10000; j++){    
            if (!test_mem_pool)
            {
                DBG_PRINT("create mem pool error");
                return 0;
            }
        //printf("count :%d \n",test_mem_pool->cold_count);
        for(i=0; i<size_t; i++)
        {
            mem_array[i] = (test_mem_t *)mem_get(test_mem_pool);
            //printf("ptr :%x \n",mem_array[i]);
        }
        //printf("count :%d \n",test_mem_pool->cold_count);
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
    int size_t = size/thread_num+20;
    printf("fun 2 size %d \n",size_t);
    test_mem_t ** mem_array   = CALLOC(size_t,sizeof(test_mem_t * )); 
    for(j=0; j<10000; j++){
        for(i=0; i<size_t; i++)
        {
            mem_array[i] = (test_mem_t *)MALLOC(sizeof(test_mem_t));
        }
        for(i=0; i<size_t; i++)
        {
            free (mem_array[i]);
        }
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
            pthread_create(&id[i],NULL,test_fun,NULL);
    }

    for(i=0;i<thread_num;++i){
            pthread_join(id[i],NULL);
    }
    //printf("count :%d \n",test_mem_pool->cold_count);

    CPU_TIME_END_PRINT("mem pool");
    TIME_END_PRINT("mem pool");
    mem_pool_destroy(test_mem_pool);

    //getchar();
    return 0;
}
/*
5000 * 10000次 1个线程
mem_pool：
mem pool,use cpu time :4.780000
mem pool,use time :4.797756

malloc:
mem pool,use cpu time :74.370000
mem pool,use time :74.467833

mem_pool_lock_free:
mem pool,use cpu time :3.150000
mem pool,use time :3.158583




5000 * 10000次 10个线程
mem_pool：
mem pool,use cpu time :94.190000
mem pool,use time :23.625192

malloc:
mem pool,use cpu time :75.890000
mem pool,use time :19.170871

mem_pool_lock_free:
mem pool,use cpu time :39.740000
mem pool,use time :9.981194

*/

#ifdef __cplusplus
}
#endif
