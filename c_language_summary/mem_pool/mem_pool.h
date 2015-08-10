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
 * __gf_*alloc: ��ͨ �ڴ�����ṹ:  
  { 
    GF_MEM_HEADER_SIZE;    //4 + sizeof (size_t) + sizeof (xlator_t *)    + 4   +     8 
                             4 + mem_size ��СN  + xlator_tָ��   + GF_MEM_HEADER_MAGIC + 8     
    char mem_size[N];      //ʵ�ʿɹ�ʹ�õ��ڴ��С 
    GF_MEM_TRAILER_SIZE; // 8�ֽڣ����ħ���� 0xBAADF00D����־�ڴ��β 
  } 
 * 
 * ÿ������ mem_size ��С���ڴ棬������������һ���ṹ���С���ڴ档 
 */ 
//32 4+8+8+4+8
#define GF_MEM_HEADER_SIZE  (4 + sizeof (size_t)  + 4 + 8)
#define GF_MEM_TRAILER_SIZE 8
#define GF_MEM_HEADER_MAGIC  0xCAFEBABE
#define GF_MEM_TRAILER_MAGIC 0xBAADF00D
#define GF_DUMP_MAX_BUF_LEN 4096
#define PATH_MAX        4096


struct mem_acct {
        uint32_t            num_types; //���ͺ�
        struct mem_acct_rec     *rec;  //ͳ����Ϣ
};

//�ڴ�ͳ����Ϣ
struct mem_acct_rec {
	const char     *typestr; //�ڴ��������֡�gf_common_mem_types_
        size_t          size; //�����С�ܺ�
        size_t          max_size; //�������С
        uint32_t        num_allocs; //�������
        uint32_t        total_allocs; //�ܷ������
        uint32_t        max_num_allocs; //���������
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

        ptr = calloc (cnt, size);/* �ڶ��Ϸ���cnt��size��С�ռ䣬����ʼ��Ϊ0 */ 
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

/* ָ�븳ֵ0xeeeeeeee��ʲô��˼ ???? */ 
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

/*�����ַ���*/
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

/*�ڴ渴��*/
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
        struct list_head  list; //�ڴ����δʹ���ڴ������ 
        int               hot_count; //�ڴ�����Ѿ�ʹ���ڴ������ 
        int               cold_count; //�ڴ����ʣ��δʹ���ڴ������ 
        gf_lock_t         lock;
        unsigned long     padded_sizeof_type; //�ڴ����ÿ����ʵ��ռ���ڴ��С
        void             *pool; //�ڴ�ؿ�ʼ��ַ
        void             *pool_end; //�ڴ�ؽ�����ַ
        int               real_sizeof_type; //�ڴ����ÿ��������ڴ��С 
        uint64_t          alloc_count; //�ڴ�����������:���뵽���� + δ���뵽�ڴ����� 
        uint64_t          pool_misses; //�ڴ��ȱ�ٴ������ڴ�������ڴ��ʧ�ܴ��� 
        int               max_alloc; //����alloc�����������
        int               curr_stdalloc; //�ڴ�������ڴ��ʧ�ܣ����´�ϵͳ�����ڴ��������ڴ��ͷ�ʱ��ֵ��һ 
        int               max_stdalloc;  //���ϵͳ��׼������� 
        char             *name; //�ڴ������
        struct list_head  global_list; //��������ȫ���ڴ������ THIS->ctx->mempool_list ��
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

