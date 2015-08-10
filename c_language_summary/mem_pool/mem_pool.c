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
#include "locking.h"
#include "list.h"
#include "../debug/debug.h"


int mem_acct_enable = 0;
struct mem_acct     mem_acct;  //�ڴ�ͳ��
struct list_head    mempool_list; // init in main
static int gf_dump_fd = -1;

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

#define GF_MEM_POOL_LIST_BOUNDARY        (sizeof(struct list_head))
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
        INIT_LIST_HEAD (&mempool_list);
        return;
}


//�����ڴ�ͳ��ʹ�ܱ�־
void
gf_mem_acct_enable_set ()
{
        mem_acct_enable = 1;
        return;
}

//  num_types = gf_common_mt_end +1
int
mem_acct_init (int num_types)
{
        int             i = 0;
        int             ret = 0;

        if (!mem_acct_enable)
                return 0;

        mem_acct.num_types = num_types;

        mem_acct.rec = CALLOC(num_types, sizeof(struct mem_acct_rec));

        if (mem_acct.rec) {
                return -1;
        }

        for (i = 0; i < num_types; i++) {
                ret = LOCK_INIT(&(mem_acct.rec[i].lock));
                if (ret) {
                        fprintf(stderr, "Unable to lock..errno : %d",errno);
                }
        }

        return 0;
}

//�����ڴ�ͳ����Ϣ
int
gf_mem_set_acct_info (char **alloc_ptr, size_t size,
		      uint32_t type, const char *typestr)
{

        char    *ptr = NULL;

        if (!alloc_ptr)
                return -1;

        ptr = (char *) (*alloc_ptr);

        GF_ASSERT (mem_acct.rec != NULL);
        GF_ASSERT (type <= mem_acct.num_types);

        LOCK(&mem_acct.rec[type].lock);
        {
		if (!mem_acct.rec[type].typestr)
            mem_acct.rec[type].typestr = typestr;
            mem_acct.rec[type].size += size;
            mem_acct.rec[type].num_allocs++;
            mem_acct.rec[type].total_allocs++;
            mem_acct.rec[type].max_size =
                max (mem_acct.rec[type].max_size,
                    mem_acct.rec[type].size);
            mem_acct.rec[type].max_num_allocs =
                max (mem_acct.rec[type].max_num_allocs,
                    mem_acct.rec[type].num_allocs);
        }
        UNLOCK(&mem_acct.rec[type].lock);
        // http://blog.csdn.net/wangyuling1234567890/article/details/24564891 ��ͨ�ڴ����ṹ�д���
        //ͷ��С: GF_MEM_HEADER_SIZE   (4 + sizeof (size_t) + 4 + 8)
        *(uint32_t *)(ptr) = type;
        ptr = ptr + 4;
        memcpy (ptr, &size, sizeof(size_t));
        ptr += sizeof (size_t);
        *(uint32_t *)(ptr) = GF_MEM_HEADER_MAGIC; //ħ��
        ptr = ptr + 4;
        ptr = ptr + 8; //padding ���
        //β��С: GF_MEM_TRAILER_SIZE 8
        *(uint32_t *) (ptr + size) = GF_MEM_TRAILER_MAGIC; //ħ��

        *alloc_ptr = (void *)ptr;
        return 0;
}

//��xl->mem_acct �ϼ�¼�ڴ����
/*�����ֱ�Ϊ:����������С���ڴ����ͣ���:gf_common_mt_mem_pool��
�������֣�"gf_common_mt_mem_pool"*/
void *
__gf_calloc (size_t nmemb, size_t size, uint32_t type, const char *typestr)
{
        size_t          tot_size = 0;
        size_t          req_size = 0;
        char            *ptr = NULL;

        //�����ڴ�ͳ�ƣ�ֱ�ӷ���
        if (!mem_acct_enable)
                return CALLOC (nmemb, size);

 
        // ʵ���ڴ��С
        req_size = nmemb * size;
        //ʵ���ڴ��С���� ͳ���õ�ͷ��С��β����
        tot_size = req_size + GF_MEM_HEADER_SIZE + GF_MEM_TRAILER_SIZE;

        ptr = calloc (1, tot_size);

        if (!ptr) {
                LOG_PRINT(D_LOG_CRIT,"The memory size %zu is not enough", tot_size);
                return NULL;
        }
        //����ͳ����Ϣ
        gf_mem_set_acct_info (&ptr, req_size, type, typestr);

        return (void *)ptr;
}

// ��__gf_calloc����
void *
__gf_malloc (size_t size, uint32_t type, const char *typestr)
{
        size_t          tot_size = 0;
        char            *ptr = NULL;

        if (!mem_acct_enable)
                return MALLOC (size);

        tot_size = size + GF_MEM_HEADER_SIZE + GF_MEM_TRAILER_SIZE;

        ptr = malloc (tot_size);
        if (!ptr) {
                LOG_PRINT(D_LOG_CRIT,"The memory size %zu is not enough", tot_size);
                return NULL;
        }
        gf_mem_set_acct_info (&ptr, size, type, typestr);

        return (void *)ptr;
}

//���·����ڴ��С
void *
__gf_realloc (void *ptr, size_t size)
{
        size_t          tot_size = 0;
        char            *orig_ptr = NULL;
        uint32_t        type = 0;
        char            *new_ptr;

        if (!mem_acct_enable)
                return REALLOC (ptr, size);

        tot_size = size + GF_MEM_HEADER_SIZE + GF_MEM_TRAILER_SIZE;

        orig_ptr = (char *)ptr - 8 - 4;

        GF_ASSERT (*(uint32_t *)orig_ptr == GF_MEM_HEADER_MAGIC);

        orig_ptr = (char *)ptr - GF_MEM_HEADER_SIZE;
        type = *(uint32_t *)orig_ptr;

        new_ptr = realloc (orig_ptr, tot_size);
        if (!new_ptr) {
                LOG_PRINT(D_LOG_CRIT,"The memory size %zu is not enough", tot_size);
                return NULL;
        }

        /*
         * We used to pass (char **)&ptr as the second
         * argument after the value of realloc was saved
         * in ptr, but the compiler warnings complained
         * about the casting to and forth from void ** to
         * char **.
         */
        gf_mem_set_acct_info (&new_ptr, size, type, NULL);

        return (void *)new_ptr;
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
        size_t          req_size = 0;
        char            *ptr = NULL;
        uint32_t        type = 0;

        //û���ڴ�ͳ�ƣ�ֱ���ͷ�
        if (!mem_acct_enable) {
                FREE (free_ptr);
                return;
        }

        if (!free_ptr)
                return;

        ptr = (char *)free_ptr - 8 - 4;

        //Possible corruption, assert here
        GF_ASSERT (GF_MEM_HEADER_MAGIC == *(uint32_t *)ptr);

        *(uint32_t *)ptr = 0; //��ħ����Ϊ0

        if (!mem_acct.rec) {
                ptr = (char *)free_ptr - GF_MEM_HEADER_SIZE;
                goto free;
        }


        ptr = ptr - sizeof(size_t);
        memcpy (&req_size, ptr, sizeof (size_t));
        ptr = ptr - 4;
        type = *(uint32_t *)ptr;

        // This points to a memory overrun
        GF_ASSERT (GF_MEM_TRAILER_MAGIC ==
                *(uint32_t *)((char *)free_ptr + req_size));

        *(uint32_t *) ((char *)free_ptr + req_size) = 0;

        //�ڴ�ͳ���޸�
        LOCK (&mem_acct.rec[type].lock);
        {
                mem_acct.rec[type].size -= req_size;
                mem_acct.rec[type].num_allocs--;
        }
        UNLOCK (&mem_acct.rec[type].lock);
free:
        FREE (ptr);
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
        GF_UNUSED struct list_head *list = NULL;

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

        LOCK_INIT (&mem_pool->lock);
        INIT_LIST_HEAD (&mem_pool->list);
        INIT_LIST_HEAD (&mem_pool->global_list);

        //�ܵĶ����ڴ��С���ڴ���е�ÿ������ʵ�ʷ�����ڴ��С��
        mem_pool->padded_sizeof_type = padded_sizeof_type;
        //ʹ���ڴ�ض������ʵ�ڴ��С
        mem_pool->real_sizeof_type = sizeof_type;

        //�������տ�ʼ������ģ�δʹ�õģ�
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
                INIT_LIST_HEAD (list);
                //���뵽�ڴ�ص�������ȥ
                list_add_tail (list, &mem_pool->list);
        }

        //��¼������ڴ�����
        mem_pool->pool = pool;
        //�ڴ��������ĵ�ַ 
        mem_pool->pool_end = pool + (count * (padded_sizeof_type));

        /* add this pool to the global list */
        
        //����ȫ�ֵ��ڴ������ ���ڴ�ع���: mempool_list ��
        
        list_add (&mem_pool->global_list, &mempool_list);

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
        struct list_head *list = NULL;
        void             *ptr = NULL;
        int             *in_use = NULL;
        struct mem_pool **pool_ptr = NULL;

        if (!mem_pool) {
                LOG_PRINT(D_LOG_ERR,"mem-pool invalid argument");
                return NULL;
        }

        LOCK (&mem_pool->lock);
        {
                //�ڴ���������1
                mem_pool->alloc_count++;
                //����δʹ���ڴ�
                if (mem_pool->cold_count) {
                        //����ֻ����δʹ�õ��ڴ�
                        list = mem_pool->list.next;
                        list_del (list);

                        //����ʹ���ڴ�����1
                        mem_pool->hot_count++;
                        //δʹ���ڴ�����1
                        mem_pool->cold_count--;

                        if (mem_pool->max_alloc < mem_pool->hot_count)
                                mem_pool->max_alloc = mem_pool->hot_count;

                        ptr = list;
                        //in_use ���ڴ�λ��
                        in_use = (ptr + GF_MEM_POOL_LIST_BOUNDARY +
                                  GF_MEM_POOL_PTR);
                        //��1����ʾ��ʹ��
                        *in_use = 1;

                        goto fwd_addr_out;
                }

                /* This is a problem area. If we've run out of
                 * chunks in our slab above, we need to allocate
                 * enough memory to service this request.
                 * The problem is, these individual chunks will fail
                 * the first address range check in __is_member. Now, since
                 * we're not allocating a full second slab, we wont have
                 * enough info perform the range check in __is_member.
                 *
                 * I am working around this by performing a regular allocation
                 * , just the way the caller would've done when not using the
                 * mem-pool. That also means, we're not padding the size with
                 * the list_head structure because, this will not be added to
                 * the list of chunks that belong to the mem-pool allocated
                 * initially.
                 *
                 * This is the best we can do without adding functionality for
                 * managing multiple slabs. That does not interest us at present
                 * because it is too much work knowing that a better slab
                 * allocator is coming RSN.
                 */
                //�����ǰ������ڴ治����cold_countΪ0
                mem_pool->pool_misses++; //�ڴ��ȱʧ����������1
                mem_pool->curr_stdalloc++; //ϵͳ��׼���������1  
                if (mem_pool->max_stdalloc < mem_pool->curr_stdalloc)
                        mem_pool->max_stdalloc = mem_pool->curr_stdalloc;
                ptr = GF_CALLOC (1, mem_pool->padded_sizeof_type,
                                 gf_common_mt_mem_pool);//����һ���ڴ�ض���

                /* Memory coming from the heap need not be transformed from a
                 * chunkhead to a usable pointer since it is not coming from
                 * the pool.
                 */
        }
fwd_addr_out:
        pool_ptr = mem_pool_from_ptr (ptr);// pool��ַ:ptr+LIST_BOUNDARY
        *pool_ptr = (struct mem_pool *)mem_pool;
        ptr = mem_pool_chunkhead2ptr (ptr);//ptr + POOL_PAD_BOUNDARY �õ�������ʼ���ڴ�
        UNLOCK (&mem_pool->lock);

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
        struct list_head *list = NULL;
        int    *in_use = NULL;
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
        LOCK (&pool->lock);
        {

                switch (__is_member (pool, ptr))
                {
                case 1:
                        in_use = (head + GF_MEM_POOL_LIST_BOUNDARY +
                                  GF_MEM_POOL_PTR);
                        if (!is_mem_chunk_in_use(in_use)) {
                                LOG_PRINT(D_LOG_ERR,"mem-pool mem_put called on freed ptr %p of mem "
                                                  "pool %p", ptr, pool);
                                break;
                        }
                        pool->hot_count--;
                        pool->cold_count++;
                        *in_use = 0;
                        list_add (list, &pool->list);
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
                        
                        pool->curr_stdalloc--; //ϵͳ���������1;

                        GF_FREE (list);
                        break;
                default:
                        /* log error */
                        break;
                }
        }
        UNLOCK (&pool->lock);
}

//�����ڴ��
void
mem_pool_destroy (struct mem_pool *pool)
{
        if (!pool)
                return;
        LOG_PRINT(D_LOG_INFO,"size=%lu max=%d total=%"PRIu64,
                pool->padded_sizeof_type, pool->max_alloc, pool->alloc_count);

        list_del (&pool->global_list);//��ȫ���ڴ�ض���������

        LOCK_DESTROY (&pool->lock);
        GF_FREE (pool->name);
        GF_FREE (pool->pool);
        GF_FREE (pool);

        return;
}

void cleanup_and_exit (sig)
{
    PRINT("catch signal SIGINT,exit.\n");
    exit(0);
}


int
gf_proc_dump_write_fd (char *key, char *value, va_list ap)
{

        char         buf[GF_DUMP_MAX_BUF_LEN];
        int          offset = 0;

        GF_ASSERT (key);

        offset = strlen (key);

        memset (buf, 0, GF_DUMP_MAX_BUF_LEN);
        snprintf (buf, GF_DUMP_MAX_BUF_LEN, "%s", key);
        snprintf (buf + offset, GF_DUMP_MAX_BUF_LEN - offset, "=");
        offset += 1;
        vsnprintf (buf + offset, GF_DUMP_MAX_BUF_LEN - offset, value, ap);

        offset = strlen (buf);
        snprintf (buf + offset, GF_DUMP_MAX_BUF_LEN - offset, "\n");
        return write (gf_dump_fd, buf, strlen (buf));
}


int
gf_proc_dump_write (char *key, char *value, ...)
{
	int ret = 0;
	va_list ap;

	va_start (ap, value);
	ret = gf_proc_dump_write_fd (key, value, ap);
	va_end (ap);

	return ret;
}

int
gf_proc_dump_add_section_fd (char *key, va_list ap)
{

        char buf[GF_DUMP_MAX_BUF_LEN];

        GF_ASSERT(key);

        memset (buf, 0, sizeof(buf));
        snprintf (buf, GF_DUMP_MAX_BUF_LEN, "\n[");
        vsnprintf (buf + strlen(buf),
                   GF_DUMP_MAX_BUF_LEN - strlen (buf), key, ap);
        snprintf (buf + strlen(buf),
                  GF_DUMP_MAX_BUF_LEN - strlen (buf),  "]\n");
        return write (gf_dump_fd, buf, strlen (buf));
}

int
gf_proc_dump_add_section (char *key, ...)
{
	va_list ap;
	int ret = 0;

	va_start (ap, key);

    ret = gf_proc_dump_add_section_fd (key, ap);
	va_end (ap);

	return ret;
}
static int
gf_proc_dump_open (char *tmpname)
{
        int  dump_fd = -1;

        dump_fd = mkstemp (tmpname);
        if (dump_fd < 0)
                return -1;

        gf_dump_fd = dump_fd;
        return 0;
}

static void
gf_proc_dump_close (void)
{
        close (gf_dump_fd);
        gf_dump_fd = -1;
}

static void
proc_dump_mem_info ()
{

        int     i = 0;
        struct mem_acct rec = {0,};


        if (!mem_acct.rec)
                return;

        gf_proc_dump_add_section ("Memory usage:");
        gf_proc_dump_write ("num_types", "%d", mem_acct.num_types);

        for (i = 0; i < mem_acct.num_types; i++) {
                if (!(memcmp (&mem_acct.rec[i], &rec,
                              sizeof (struct mem_acct))))
                        continue;

                gf_proc_dump_add_section ("usage-type %s memusage",
                                          mem_acct.rec[i].typestr);
                gf_proc_dump_write ("size", "%u", mem_acct.rec[i].size);
                gf_proc_dump_write ("num_allocs", "%u",
                                    mem_acct.rec[i].num_allocs);
                gf_proc_dump_write ("max_size", "%u",
                                    mem_acct.rec[i].max_size);
                gf_proc_dump_write ("max_num_allocs", "%u",
                                    mem_acct.rec[i].max_num_allocs);
                gf_proc_dump_write ("total_allocs", "%u",
                                    mem_acct.rec[i].total_allocs);
        }
        return;
}

void
gf_proc_dump_mempool_info ()
{
        struct mem_pool *pool = NULL;

        gf_proc_dump_add_section ("mempool");

        list_for_each_entry (pool, &mempool_list, global_list) {
                gf_proc_dump_write ("-----", "-----");
                gf_proc_dump_write ("pool-name", "%s", pool->name);
                gf_proc_dump_write ("hot-count", "%d", pool->hot_count);
                gf_proc_dump_write ("cold-count", "%d", pool->cold_count);
                gf_proc_dump_write ("padded_sizeof", "%lu",
                                    pool->padded_sizeof_type);
                gf_proc_dump_write ("alloc-count", "%"PRIu64, pool->alloc_count);
                gf_proc_dump_write ("max-alloc", "%d", pool->max_alloc);

                gf_proc_dump_write ("pool-misses", "%"PRIu64, pool->pool_misses);
                gf_proc_dump_write ("cur-stdalloc", "%d", pool->curr_stdalloc);
                gf_proc_dump_write ("max-stdalloc", "%d", pool->max_stdalloc);
        }
}


void proc_dump_info (sig)
{
    int ret;
    char tmp_dump_name[PATH_MAX] = {0,};
    char path[PATH_MAX] = {0,};
    snprintf (tmp_dump_name, PATH_MAX, "%s/dump.XXXXXX","/var/run");
    snprintf (path, PATH_MAX, "%s/dump.%d","/var/run",getpid());

    ret = gf_proc_dump_open (tmp_dump_name);
    if (ret < 0)
            return;
    proc_dump_mem_info();
    gf_proc_dump_mempool_info();
    gf_proc_dump_close();
    PRINT("catch signal SIGUSR1, dump mem info in %s\n", path);
    rename (tmp_dump_name, path);
}

static void sig_fun(int sig)
{

    switch (sig) 
    {
        case SIGINT:
        case SIGTERM:
                cleanup_and_exit (sig);
                break;
        case SIGUSR1:
                proc_dump_info (sig);
                break;
        default:
                break;
    }
}
   
void  signals_setup()
{
    /*
    struct sigaction act;
    act.sa_handler = sig_fun;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (sigaction(SIGINT, &act, NULL) < 0)
        DBG_PRINT("setup signal error");
    if (sigaction(SIGTERM, &act, NULL) < 0)
        DBG_PRINT("setup signal error");
    if (sigaction(SIGUSR1, &act, NULL) < 0)
        DBG_PRINT("setup signal error");
    */
    signal (SIGINT, sig_fun);
    signal (SIGTERM, sig_fun);
    signal (SIGUSR1, sig_fun);
}



#ifdef __cplusplus
}
#endif
