#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*������ uint64_t��*/
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
 * gf mem_pool ���ڴ�������ڴ�ṹ:  
  { 
    struct list_head;   // ��mem_pool_new_fn�г�ʼ��: INIT_LIST_HEAD (list);
    struct mem_pool*;   // ��mem_get�г�ʼ��: *pool_ptr = (struct mem_pool *)mem_pool;
    int in_use;        //���ڴ���Ƿ�ʹ��: 1��ʾ��ʹ��, 0��ʾδʹ�� 
    char mem_size[N];  //ʵ�ʿɹ�ʹ�õ��ڴ��С 
  } 
 * 
 * ÿ���ڴ������ mem_size ��С���ڴ棬gf��ʽ���붼����������һ���ṹ���С���ڴ档 
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



//��xl->mem_acct �ϼ�¼�ڴ����
/*�����ֱ�Ϊ:����������С���ڴ����ͣ���:gf_common_mt_mem_pool��
�������֣�"gf_common_mt_mem_pool"*/
void *
__gf_calloc (size_t nmemb, size_t size, uint32_t type, const char *typestr)
{

       return CALLOC (nmemb, size);

}

// ��__gf_calloc����
void *
__gf_malloc (size_t size, uint32_t type, const char *typestr)
{

        return MALLOC (size);

}

//���·����ڴ��С
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


/*�½�һ���ڴ�ض���Ȼ���մ��ݽ������ڴ�Ĵ�С�͸��������ڴ棬��Ҫ����һЩ��
��洢���ݵ��ڴ���������������ָ�����Ϊ��Щ�ڴ�ض�������ͨ��ͨ������������
�ģ��������ʶ�ڴ��Ƿ��ڱ�ʹ�õ�һ����־��
http://blog.csdn.net/wangyuling1234567890/article/details/24564891
*/
struct mem_pool *
mem_pool_new_fn (unsigned long sizeof_type,
                 unsigned long count, char *name)//��������˼�����ǣ�ÿ������ĳ��ȣ��ڴ�ط������ĸ������ڴ�ص����֡�
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
        /*����һЩ����洢���ݵ��ڴ�����*/
        //�����С����������ռ�ڴ�+����ͷ+�ڴ��ָ��+int�ڴ��С�����in_use������
        padded_sizeof_type = sizeof_type + GF_MEM_POOL_PAD_BOUNDARY;

        //���ڴ�ص�ͷ�������ڴ�ռ�
        mem_pool = GF_CALLOC (sizeof (*mem_pool), 1, gf_common_mt_mem_pool);
        if (!mem_pool)
                return NULL;
        //�ڴ������
        ret = gf_asprintf (&mem_pool->name, "%s", name);
        if (ret < 0)
                return NULL;

        if (!mem_pool->name) {
                GF_FREE (mem_pool);
                return NULL;
        }

 
        MY_INIT_LIST_HEAD (&mem_pool->list);
        MY_INIT_LIST_HEAD (&mem_pool->global_list);

        //�ܵĶ����ڴ��С���ڴ���е�ÿ������ʵ�ʷ�����ڴ��С��
        mem_pool->padded_sizeof_type = padded_sizeof_type;
        //ʹ���ڴ�ض������ʵ�ڴ��С
        mem_pool->real_sizeof_type = sizeof_type;

        mem_pool->cold_count = count;
        pool = GF_CALLOC (count, padded_sizeof_type, gf_common_mt_long);
        if (!pool) {
                GF_FREE (mem_pool->name);
                GF_FREE (mem_pool);
                return NULL;
        }

        for (i = 0; i < count; i++) {
                //����ÿһ���ڴ�����С������
                list = pool + (i * (padded_sizeof_type));
                //�ڴ��ǰ����Ǵ������ͷ GF_MEM_POOL_LIST_BOUNDARY
                MY_INIT_LIST_HEAD (list);
                //���뵽�ڴ�ص�������ȥ
                my_list_add(list, &mem_pool->list);
        }

        //��¼������ڴ�����
        mem_pool->pool = pool;
        //�ڴ��������ĵ�ַ 
        mem_pool->pool_end = pool + (count * (padded_sizeof_type));

        /* add this pool to the global list */
        
        //����ȫ�ֵ��ڴ������ ���ڴ�ع���: mempool_list ��
        
        my_list_add (&mem_pool->global_list, &mempool_list);

        return mem_pool;
}

//���ڴ�����ó�һ�������ڴ��,����ʼ��Ϊ0
void*
mem_get0 (struct mem_pool *mem_pool)
{
        void             *ptr = NULL;

        if (!mem_pool) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return NULL;
        }

        ptr = mem_get(mem_pool);//�õ�һ���ڴ�����

        if (ptr)
                memset(ptr, 0, mem_pool->real_sizeof_type);//��ʼ��0 

        return ptr;
}

/*���������Ҫʹ�������ڴ���е��ڴ棬��ô�ʹ��ڴ�����ó�һ�����󣨲�ͬ������Ҫ
��ͬ���ڴ�ض��󱣴棬ÿһ���ڴ�ض���ֻ����һ�ֶ�����ڴ�ṹ�����ڴ�*/
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


        //����δʹ���ڴ�
        if (mem_pool->list.next != NULL) {
                //����ֻ����δʹ�õ��ڴ�
                list = list_del_and_get(&mem_pool->list);
                // ���ܻᾺ������
                if (list == NULL )
                    {
                    list = CALLOC (1, mem_pool->padded_sizeof_type);//����һ���ڴ�ض���
                    //printf("out of pool\n ");
                    }
                ptr = list;
                //in_use ���ڴ�λ��
                in_use = (ptr + GF_MEM_POOL_LIST_BOUNDARY +
                          GF_MEM_POOL_PTR);
                //��1����ʾ��ʹ��
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
        ptr = CALLOC (1, mem_pool->padded_sizeof_type);//����һ���ڴ�ض���
        //free(ptr);
        //ptr = CALLOC (1, mem_pool->padded_sizeof_type);
        //printf("out of pool\n ");
        //printf("%u\n ",ptr);
        }

        pool_ptr = mem_pool_from_ptr (ptr);// pool��ַ:ptr+LIST_BOUNDARY
        *pool_ptr = (struct mem_pool *)mem_pool;
        ptr = mem_pool_chunkhead2ptr (ptr);//ptr + POOL_PAD_BOUNDARY �õ�������ʼ���ڴ�

        return ptr;
}

/*������ʹ����һ���ڴ���е��ڴ�ṹ�Ժ����Ҫ�����ڴ���Ա㱻�Ժ�ĳ���ʹ�ã�
�ﵽѭ��ʹ�õ�Ŀ�ġ������ڹ黹��ǰ����������Ҫ�ж��ǲ����ڴ�ض����һ����Ա��
�жϵĽ�������֣��ֱ��ǣ��ǣ����Ǻʹ�����������������ڴ�ص��ڴ淶Χ���ڣ�
���ǲ������ڴ�ض���Ĵ�С����ʵ������*/
static int
__is_member (struct mem_pool *pool, void *ptr) //�ж�ptrָ����ڴ��Ƿ���pool�ĳ�Ա
{
        if (!pool || !ptr) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return -1;
        }

        if (ptr < pool->pool || ptr >= pool->pool_end) //ptr�������pool��ʼ�������ķ�Χ�ھͲ���
                return 0;

        if ((mem_pool_ptr2chunkhead (ptr) - pool->pool)
            % pool->padded_sizeof_type)//�ж��Ƿ���һ�������ڴ���С���ڴ����
                return -1;

        return 1;
}

//��ptr�Żص��ڴ����ȥ
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

        //�ڴ��ͷ��ַ
        list = head = mem_pool_ptr2chunkhead (ptr);
        // ָ�� mem_pool��ַ�ĵ�ַ
        tmp = mem_pool_from_ptr (head);
        if (!tmp) {
                LOG_PRINT(D_LOG_ERR,"mem-pool ptr header is corrupted");
                return;
        }
        //mem_pool��ַ
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
        case 0: //�����ڴ���е��ڴ�ֱ���ͷŵ�
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

//�����ڴ��
void
mem_pool_destroy (struct mem_pool *pool)
{
        if (!pool)
                return;
        LOG_PRINT(D_LOG_INFO,"size=%lu max=%d total=%"PRIu64,
                pool->padded_sizeof_type, pool->max_alloc, pool->alloc_count);

        list_del_and_get(&pool->global_list);//��ȫ���ڴ�ض���������

        GF_FREE (pool->name);
        GF_FREE (pool->pool);
        GF_FREE (pool);

        return;
}





#ifdef __cplusplus
}
#endif
