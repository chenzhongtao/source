#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


#include "mem_pool.h"
#include "list.h"
#include "../debug/debug.h"


struct my_list_head    mempool_list; // init in main

/* 
 * gf mem_pool 中内存块申请内存结构:  
  { 
    struct list_head;   // 在mem_pool_new_fn中初始化: INIT_LIST_HEAD (list);
    struct mem_pool*;   // 在mem_get中初始化: *pool_ptr = (struct mem_pool *)mem_pool;
    int in_use;        //该内存块是否被使用: 1表示被使用, 0表示未使用 
    char mem_size[N];  //实际可供使用的内存大小 
  } 
 * 
 * 每次内存池申请 mem_size 大小的内存，gf方式申请都会申请上面一个结构体大小的内存。 
 */ 

#define GF_MEM_POOL_LIST_BOUNDARY        (sizeof(struct my_list_head))
#define GF_MEM_POOL_PTR                  (sizeof(struct mem_pool*))
#define GF_MEM_POOL_PAD_BOUNDARY         (GF_MEM_POOL_LIST_BOUNDARY  + GF_MEM_POOL_PTR + sizeof(int))
#define mem_pool_chunkhead2ptr(head)     ((head) + GF_MEM_POOL_PAD_BOUNDARY)
#define mem_pool_ptr2chunkhead(ptr)      ((ptr) - GF_MEM_POOL_PAD_BOUNDARY)
#define is_mem_chunk_in_use(ptr)         (*ptr == 1)
#define mem_pool_from_ptr(ptr)           ((ptr) + GF_MEM_POOL_LIST_BOUNDARY)



#define GLUSTERFS_ENV_MEM_ACCT_STR  "GLUSTERFS_DISABLE_MEM_ACCT"



void
gf_mem_init_mempool_list ()
{
        MY_INIT_LIST_HEAD (&mempool_list);
        return;
}



//在xl->mem_acct 上记录内存分配
/*参数分别为:分配数，大小，内存类型，如:gf_common_mt_mem_pool，
类型名字，"gf_common_mt_mem_pool"*/
void *
__gf_calloc (size_t nmemb, size_t size, uint32_t type, const char *typestr)
{

       return CALLOC (nmemb, size);

}

// 与__gf_calloc类似
void *
__gf_malloc (size_t size, uint32_t type, const char *typestr)
{

        return MALLOC (size);

}

//重新分配内存大小
void *
__gf_realloc (void *ptr, size_t size)
{

        return REALLOC (ptr, size);

}

int
gf_vasprintf (char **string_ptr, const char *format, va_list arg)
{
        va_list arg_save;
        char    *str = NULL;
        int     size = 0;
        int     rv = 0;

        if (!string_ptr || !format)
                return -1;

        va_copy (arg_save, arg);

        size = vsnprintf (NULL, 0, format, arg);
        size++;
        str = GF_MALLOC (size, gf_common_mt_asprintf);
        if (str == NULL) {
                /* log is done in GF_MALLOC itself */
                return -1;
        }
        rv = vsnprintf (str, size, format, arg_save);

        *string_ptr = str;
        return (rv);
}

int
gf_asprintf (char **string_ptr, const char *format, ...)
{
        va_list arg;
        int     rv = 0;

        va_start (arg, format);
        rv = gf_vasprintf (string_ptr, format, arg);
        va_end (arg);

        return rv;
}

void
__gf_free (void *free_ptr)
{

        FREE (free_ptr);

}


/*新建一个内存池对象，然后按照传递进来的内存的大小和个数分配内存，还要加上一些额
外存储内容的内存容量，如存放链表指针的因为这些内存池对象本身是通过通用链表来管理
的，还有如标识内存是否在被使用的一个标志等
http://blog.csdn.net/wangyuling1234567890/article/details/24564891
*/
struct mem_pool *
mem_pool_new_fn (unsigned long sizeof_type,
                 unsigned long count, char *name)//参数的意思依次是：每个对象的长度，内存池分配对象的个数，内存池的名字。
{
        struct mem_pool  *mem_pool = NULL;
        unsigned long     padded_sizeof_type = 0;
        GF_UNUSED void             *pool = NULL;
        GF_UNUSED int               i = 0;
        int               ret = 0;
        GF_UNUSED struct my_list_head *list = NULL;

        if (!sizeof_type || !count) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return NULL;
        }
        /*加上一些额外存储内容的内存容量*/
        //计算大小：对象本身所占内存+链表头+内存池指针+int内存大小（存放in_use变量）
        padded_sizeof_type = sizeof_type + GF_MEM_POOL_PAD_BOUNDARY;

        //给内存池的头结点分配内存空间
        mem_pool = GF_CALLOC (sizeof (*mem_pool), 1, gf_common_mt_mem_pool);
        if (!mem_pool)
                return NULL;
        //内存池名字
        ret = gf_asprintf (&mem_pool->name, "%s", name);
        if (ret < 0)
                return NULL;

        if (!mem_pool->name) {
                GF_FREE (mem_pool);
                return NULL;
        }

 
        MY_INIT_LIST_HEAD (&mem_pool->list);
        MY_INIT_LIST_HEAD (&mem_pool->global_list);

        //总的对齐内存大小，内存池中的每个对象实际分配的内存大小。
        mem_pool->padded_sizeof_type = padded_sizeof_type;
        //使用内存池对象的真实内存大小
        mem_pool->real_sizeof_type = sizeof_type;

        mem_pool->cold_count = count;
        pool = GF_CALLOC (count, padded_sizeof_type, gf_common_mt_long);
        if (!pool) {
                GF_FREE (mem_pool->name);
                GF_FREE (mem_pool);
                return NULL;
        }

        for (i = 0; i < count; i++) {
                //分配每一个内存对象大小到链表
                list = pool + (i * (padded_sizeof_type));
                //内存的前面就是存放链表头 GF_MEM_POOL_LIST_BOUNDARY
                MY_INIT_LIST_HEAD (list);
                //加入到内存池的链表中去
                my_list_add(list, &mem_pool->list);
        }

        //记录分配的内存区域
        mem_pool->pool = pool;
        //内存分配结束的地址 
        mem_pool->pool_end = pool + (count * (padded_sizeof_type));

        /* add this pool to the global list */
        
        //加入全局的内存池链表 ，内存池挂在: mempool_list 上
        
        my_list_add (&mem_pool->global_list, &mempool_list);

        return mem_pool;
}

//从内存池中拿出一个对象内存块,并初始化为0
void*
mem_get0 (struct mem_pool *mem_pool)
{
        void             *ptr = NULL;

        if (!mem_pool) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return NULL;
        }

        ptr = mem_get(mem_pool);//得到一个内存对象块

        if (ptr)
                memset(ptr, 0, mem_pool->real_sizeof_type);//初始化0 

        return ptr;
}

/*如果我们需要使用这种内存池中的内存，那么就从内存池中拿出一个对象（不同对象需要
不同的内存池对象保存，每一个内存池对象只保存一种对象的内存结构）的内存*/
void *
mem_get (struct mem_pool *mem_pool)
{
        struct my_list_head *list = NULL;
        void             *ptr = NULL;
        int             *in_use = NULL;
        struct mem_pool **pool_ptr = NULL;

        if (!mem_pool) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return NULL;
        }


        //还有未使用内存
        if (mem_pool->list.next != NULL) {
                //链表只保存未使用的内存
                list = list_del_and_get(&mem_pool->list);
                // 可能会竞争不到
                if (list == NULL )
                    {
                    list = CALLOC (1, mem_pool->padded_sizeof_type);//分配一个内存池对象
                    //printf("out of pool\n ");
                    }
                ptr = list;
                //in_use 的内存位置
                in_use = (ptr + GF_MEM_POOL_LIST_BOUNDARY +
                          GF_MEM_POOL_PTR);
                //置1，表示在使用
                *in_use = 1;
                /*
                int tmp;
                do {
                    tmp = mem_pool->cold_count;
                }while(!CAS(&mem_pool->cold_count, tmp, tmp-1));
                */

        }
        else
        {
        ptr = CALLOC (1, mem_pool->padded_sizeof_type);//分配一个内存池对象
        //free(ptr);
        //ptr = CALLOC (1, mem_pool->padded_sizeof_type);
        //printf("out of pool\n ");
        //printf("%u\n ",ptr);
        }

        pool_ptr = mem_pool_from_ptr (ptr);// pool地址:ptr+LIST_BOUNDARY
        *pool_ptr = (struct mem_pool *)mem_pool;
        ptr = mem_pool_chunkhead2ptr (ptr);//ptr + POOL_PAD_BOUNDARY 得到真正开始的内存

        return ptr;
}

/*当我们使用完一个内存池中的内存结构以后就需要还给内存池以便被以后的程序使用，
达到循环使用的目的。但是在归还以前我们首先需要判断是不是内存池对象的一个成员，
判断的结果有三种，分别是：是，不是和错误情况（就是它在内存池的内存范围以内，
但是不符合内存池对象的大小），实现如下*/
static int
__is_member (struct mem_pool *pool, void *ptr) //判断ptr指向的内存是否是pool的成员
{
        if (!pool || !ptr) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return -1;
        }

        if (ptr < pool->pool || ptr >= pool->pool_end) //ptr如果不再pool开始到结束的范围内就不是
                return 0;

        if ((mem_pool_ptr2chunkhead (ptr) - pool->pool)
            % pool->padded_sizeof_type)//判断是否是一个符合内存块大小的内存对象
                return -1;

        return 1;
}

//将ptr放回到内存池中去
void
mem_put (void *ptr)
{
        struct my_list_head *list = NULL;
        void   *head = NULL;
        struct mem_pool **tmp = NULL;
        struct mem_pool *pool = NULL;

        if (!ptr) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return;
        }

        //内存的头地址
        list = head = mem_pool_ptr2chunkhead (ptr);
        // 指向 mem_pool地址的地址
        tmp = mem_pool_from_ptr (head);
        if (!tmp) {
                LOG_PRINT(D_LOG_ERR,"mem-pool ptr header is corrupted");
                return;
        }
        //mem_pool地址
        pool = *tmp;
        if (!pool) {
                LOG_PRINT(D_LOG_ERR,"mem-pool ptr is NULL");
                return;
        }
        
        switch (__is_member (pool, ptr))
        {
        case 1:
                my_list_add (list, &pool->list);
                break;
        case -1:
                /* For some reason, the address given is within
                 * the address range of the mem-pool but does not align
                 * with the expected start of a chunk that includes
                 * the list headers also. Sounds like a problem in
                 * layers of clouds up above us. ;)
                 */
                abort ();
                break;
        case 0: //不是内存池中的内存直接释放掉
                /* The address is outside the range of the mem-pool. We
                 * assume here that this address was allocated at a
                 * point when the mem-pool was out of chunks in mem_get
                 * or the programmer has made a mistake by calling the
                 * wrong de-allocation interface. We do
                 * not have enough info to distinguish between the two
                 * situations.
                 */
                //printf("%u\n ",list);
                FREE (list);
                break;
        default:
                /* log error */
                break;
        }



}

//销毁内存池
void
mem_pool_destroy (struct mem_pool *pool)
{
        if (!pool)
                return;
        LOG_PRINT(D_LOG_INFO,"size=%lu max=%d total=%"PRIu64,
                pool->padded_sizeof_type, pool->max_alloc, pool->alloc_count);

        list_del_and_get(&pool->global_list);//从全局内存池对象中脱链

        GF_FREE (pool->name);
        GF_FREE (pool->pool);
        GF_FREE (pool);

        return;
}





#ifdef __cplusplus
}
#endif
