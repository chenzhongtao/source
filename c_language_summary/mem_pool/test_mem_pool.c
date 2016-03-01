#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <unistd.h> //getopt
#include <stdio.h>
#include <pthread.h>
#include "mem_pool.h"
#include "../count_time/count_time.h"

static int block_size = 4*1024*1024 ;
static int thread_num = 1 ;
static int block_num  = 200 ;
static int loop =  10000 ;

struct _test_mem_t {
        char a[10240];
};

typedef struct _test_mem_t test_mem_t;


struct mem_pool *test_mem_pool;

static void usage(void)
{
    printf("optional arguments:\n"
           "-h,  show this help message and exit\n"
           "-b *B,*K,*M,  block size.\n"
           "-n int,  block num \n"
           "-t int,  thread num \n"
           "-l int,  loop num \n");
}

/*
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
*/
void *test_fun(void *arg)
{
    int j;
    int i;
    char ** mem_array   = CALLOC(block_num, sizeof(char *));
    for(i=0; i<block_num; i++)
    {
            mem_array[i] = (char *)MALLOC(block_size);// malloc分配内存只是现在虚拟空间上分配，只是物理空间是没有被占用的
            //mem_array[i] = (char *)CALLOC(block_size, sizeof(char));// 占用物理空间，很消耗cpu,主要是__memset_sse2
    }
    
    for(j=0; j<loop; j++){
        for(i=0; i<block_num; i++)
        {
            if(mem_array[i] != NULL)
            {
                free (mem_array[i]);
            }
            mem_array[i] = (char *)MALLOC(block_size);
            //mem_array[i] = (char *)CALLOC(block_size, sizeof(char));
        }
    }
    return 0;
}

int32_t main(int32_t argc, char **argv)
{

    int i=0;
    char *buf;
    char c;
    char unit = '\0';
    uint64_t size_max;

    while (-1 != (c = getopt(argc, argv,
                             "b:"
                             "n:"
                             "t:"
                             "l:"
                             "h"
                            )))
    {
        switch (c)
        {
        case 'b':
            buf = strdup(optarg);
            unit = buf[strlen(buf)-1];
            if (unit == 'k' || unit == 'm' ||
                    unit == 'K' || unit == 'M' ||
                    unit == 'g' || unit == 'G' ||
                    unit == 'b' || unit == 'B' )
            {
                buf[strlen(buf)-1] = '\0';
                size_max = atoi(buf);
                if (unit == 'k' || unit == 'K')
                    size_max *= 1024;
                if (unit == 'm' || unit == 'M')
                    size_max *= 1024 * 1024;
                if (unit == 'g' || unit == 'G')
                    size_max *= 1024 * 1024 * 1024;
                block_size = size_max;
            }
            break;
        case 'n':
            buf = strdup(optarg);
            block_num  = atoi(buf);
            break;
        case 't':
            buf = strdup(optarg);
            thread_num  = atoi(buf);
            break;
        case 'l':
            buf = strdup(optarg);
            loop  = atoi(buf);
            break;
        case 'h':
            usage();
            exit(0);
            break;
        }
    }
    printf("block_size = %d; block_num  = %d; thread_num = %d; loop  = %d\n",block_size, block_num, thread_num, loop);

/*
    gf_mem_init_mempool_list();

    CPU_TIME_START;
    TIME_START;
    test_mem_pool = mem_pool_new (test_mem_t, size);
    CPU_TIME_END_PRINT("mem pool");
    TIME_END_PRINT("mem pool");
    */
    CPU_TIME_START;
    TIME_START;

    pthread_t id[thread_num];

    for(i=0;i<thread_num;++i){
            pthread_create(&id[i],NULL,test_fun,NULL);
    }

    for(i=0;i<thread_num;++i){
            pthread_join(id[i],NULL);
    }

    CPU_TIME_END_PRINT("mem pool");
    TIME_END_PRINT("mem pool");
    /*
    mem_pool_destroy(test_mem_pool);
    */

    //getchar();
    return 0;
}

#ifdef __cplusplus
}
#endif
