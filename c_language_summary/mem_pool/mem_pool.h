#ifdef __cplusplus
extern "C"{
#endif

#ifndef __MEM_POOL_H__
#define __MEM_POOL_H__

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>
#include "list.h"
#include "locking.h"
#include "mem_types.h"
#include "../debug/debug.h"



#define GF_UNUSED __attribute__((unused))

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define GF_ASSERT(cond) assert(cond)


/* 
 * __gf_*alloc: 普通 内存申请结构:  
  { 
    GF_MEM_HEADER_SIZE;    //4 + sizeof (size_t) + sizeof (xlator_t *)    + 4   +     8 
                             4 + mem_size 大小N  + xlator_t指针   + GF_MEM_HEADER_MAGIC + 8     
    char mem_size[N];      //实际可供使用的内存大小 
    GF_MEM_TRAILER_SIZE; // 8字节，填充魔术字 0xBAADF00D，标志内存结尾 
  } 
 * 
 * 每次申请 mem_size 大小的内存，都会申请上面一个结构体大小的内存。 
 */ 
//32 4+8+8+4+8
#define GF_MEM_HEADER_SIZE  (4 + sizeof (size_t)  + 4 + 8)
#define GF_MEM_TRAILER_SIZE 8
#define GF_MEM_HEADER_MAGIC  0xCAFEBABE
#define GF_MEM_TRAILER_MAGIC 0xBAADF00D
#define GF_DUMP_MAX_BUF_LEN 4096
#define PATH_MAX        4096


struct mem_acct {
        uint32_t            num_types; //类型号
        struct mem_acct_rec     *rec;  //统计信息
};

//内存统计信息
struct mem_acct_rec {
	const char     *typestr; //内存类型名字。gf_common_mem_types_
        size_t          size; //分配大小总和
        size_t          max_size; //最大分配大小
        uint32_t        num_allocs; //分配次数
        uint32_t        total_allocs; //总分配次数
        uint32_t        max_num_allocs; //最大分配次数
        gf_lock_t       lock;
};


void *
__gf_calloc (size_t cnt, size_t size, uint32_t type, const char *typestr);

void *
__gf_malloc (size_t size, uint32_t type, const char *typestr);

void *
__gf_realloc (void *ptr, size_t size);

int
gf_vasprintf (char **string_ptr, const char *format, va_list arg);

int
gf_asprintf (char **string_ptr, const char *format, ...);

void
__gf_free (void *ptr);


static inline
void* __gf_default_malloc (size_t size)
{
        void *ptr = NULL;

        ptr = malloc (size);
        if (!ptr)
                LOG_PRINT(D_LOG_CRIT,"The memory size %zu is not enough", size);

        return ptr;
}

static inline
void* __gf_default_calloc (int cnt, size_t size)
{
        void *ptr = NULL;

        ptr = calloc (cnt, size);/* 在堆上分配cnt个size大小空间，并初始化为0 */ 
        if (!ptr)
                LOG_PRINT(D_LOG_CRIT,"The memory size %zu is not enough", size);

        return ptr;
}

static inline
void* __gf_default_realloc (void *oldptr, size_t size)
{
        void *ptr = NULL;

        ptr = realloc (oldptr, size);
        if (!ptr)
                LOG_PRINT(D_LOG_CRIT,"The memory size %zu is not enough", size);

        return ptr;
}

#define MALLOC(size)       __gf_default_malloc(size)
#define CALLOC(cnt,size)   __gf_default_calloc(cnt,size)
#define REALLOC(ptr,size)  __gf_default_realloc(ptr,size)

/* 指针赋值0xeeeeeeee是什么意思 ???? */ 
#define FREE(ptr)                               \
        if (ptr != NULL) {                      \
                free ((void *)ptr);             \
                ptr = (void *)0xeeeeeeee;       \
        }

#define GF_CALLOC(nmemb, size, type) __gf_calloc (nmemb, size, type, #type)

#define GF_MALLOC(size, type)  __gf_malloc (size, type, #type)

#define GF_REALLOC(ptr, size)  __gf_realloc (ptr, size)

#define GF_FREE(free_ptr) __gf_free (free_ptr)

static inline
char *gf_strndup (const char *src, size_t len)
{
        char *dup_str = NULL;

        if (!src) {
                goto out;
        }

        dup_str = GF_CALLOC (1, len + 1, gf_common_mt_strdup);
        if (!dup_str) {
                goto out;
        }

        memcpy (dup_str, src, len);
out:
        return dup_str;
}

/*复制字符串*/
static inline
char * gf_strdup (const char *src)
{

        char    *dup_str = NULL;
        size_t  len = 0;

        len = strlen (src) + 1;

        dup_str = GF_CALLOC(1, len, gf_common_mt_strdup);

        if (!dup_str)
                return NULL;

        memcpy (dup_str, src, len);

        return dup_str;
}

/*内存复制*/
static inline void *
gf_memdup (const void *src, size_t size)
{
        void *dup_mem = NULL;

        dup_mem = GF_CALLOC(1, size, gf_common_mt_strdup);
        if (!dup_mem)
                goto out;

        memcpy (dup_mem, src, size);

out:
        return dup_mem;
}

struct mem_pool {
        struct list_head  list; //内存池中未使用内存块链表 
        int               hot_count; //内存池中已经使用内存块数量 
        int               cold_count; //内存池中剩余未使用内存块数量 
        gf_lock_t         lock;
        unsigned long     padded_sizeof_type; //内存池中每个块实际占用内存大小
        void             *pool; //内存池开始地址
        void             *pool_end; //内存池结束地址
        int               real_sizeof_type; //内存池中每个块可用内存大小 
        uint64_t          alloc_count; //内存池总申请次数:申请到次数 + 未申请到内存块次数 
        uint64_t          pool_misses; //内存池缺少次数，内存池申请内存块失败次数 
        int               max_alloc; //采用alloc分配的最大次数
        int               curr_stdalloc; //内存池申请内存块失败，重新从系统申请内存块个数。内存释放时该值减一 
        int               max_stdalloc;  //最大系统标准分配次数 
        char             *name; //内存池名字
        struct list_head  global_list; //用来挂在全局内存池链表 THIS->ctx->mempool_list 上
};

struct mem_pool *
mem_pool_new_fn (unsigned long sizeof_type, unsigned long count, char *name);

#define mem_pool_new(type,count) mem_pool_new_fn (sizeof(type), count, #type)

void mem_put (void *ptr);
void *mem_get (struct mem_pool *pool);
void *mem_get0 (struct mem_pool *pool);

void mem_pool_destroy (struct mem_pool *pool);

void gf_mem_acct_enable_set ();

int mem_acct_init (int num_types);

void gf_mem_init_mempool_list ();

void  signals_setup();

#endif /* _MEM_POOL_H */

#ifdef __cplusplus
}
#endif

