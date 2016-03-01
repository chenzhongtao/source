#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include "mem_pool.h"
#include "../count_time/count_time.h"

#define size  5000

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

int32_t main(int32_t argc, char **argv)
{
      
    struct mem_pool *test_mem_pool;
    struct mem_pool *test_mem_pool_2;
    struct mem_pool *test_mem_pool_3;
    gf_mem_init_mempool_list();
    gf_mem_acct_enable_set ();
    signals_setup();
    mem_acct_init(gf_common_mt_end+1);
    test_mem_t ** mem_array   = CALLOC(size,sizeof(test_mem_t * )); 
    test_mem_2_t ** mem_array2  = CALLOC(size,sizeof(test_mem_2_t * ));
    test_mem_3_t ** mem_array3  = CALLOC(size,sizeof(test_mem_3_t * ));
    int j;
    int i;
    CPU_TIME_START;
    test_mem_pool = mem_pool_new (test_mem_t, size);
    test_mem_pool_2 = mem_pool_new (test_mem_2_t, size);
    test_mem_pool_3 = mem_pool_new (test_mem_3_t, size);
    CPU_TIME_END_PRINT("mem pool");
    CPU_TIME_START;
    for(j=0; j<10000; j++){    
            if (!test_mem_pool)
            {
                DBG_PRINT("create mem pool error");
                return -1;
            }
        for(i=0; i<size; i++)
            mem_array[i] = (test_mem_t *)mem_get(test_mem_pool);
            mem_array2[i] = (test_mem_2_t *)mem_get(test_mem_pool_2);
            mem_array3[i] = (test_mem_3_t *)mem_get(test_mem_pool_3);
        for(i=0; i<size; i++)
            mem_put(mem_array[i]) ;
            mem_put(mem_array2[i]) ;
            mem_put(mem_array3[i]) ;
        
    }
    CPU_TIME_END_PRINT("mem pool");
    mem_pool_destroy(test_mem_pool);
    mem_pool_destroy(test_mem_pool_2);
    mem_pool_destroy(test_mem_pool_3);
    CPU_TIME_START;
    for(j=0; j<100; j++){
        for(i=0; i<size; i++)
            mem_array[i] = (test_mem_t *)MALLOC(sizeof(test_mem_t));
            mem_array2[i] = (test_mem_2_t *)MALLOC(sizeof(test_mem_2_t));
            mem_array3[i] = (test_mem_3_t *)MALLOC(sizeof(test_mem_3_t));
        for(i=0; i<size; i++)
            free (mem_array[i]);
            free (mem_array2[i]);
            free (mem_array3[i]);
    }
    CPU_TIME_END_PRINT("not mem pool");
    
    //getchar();
    return 0;
}

#ifdef __cplusplus
}
#endif
