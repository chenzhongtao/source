#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h> /*定义了 uint64_t等*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "locking.h"
#include "../bst.h"
#include "../../c_language_summary/debug/debug.h"



//bst的一项
typedef struct bst_entry {
        void            *data;
        void            *key;
        int              keylen;
} bst_entry_t;


typedef struct bstree_table {
        struct bst_table *table;
        gf_lock_t       tablelock;
} bstree_table_t;


//需要自己定义一个比较函数
int
bstree_comparator (void *entry1, void *entry2, void *param)
{
        int             ret = 0;
        bst_entry_t *e1 = NULL;
        bst_entry_t *e2 = NULL;

        if ((!entry1) || (!entry2) || (!param))
                return -1;

        e1 = (bst_entry_t *)entry1;
        e2 = (bst_entry_t *)entry2;

        // key长的那个大
        if (e1->keylen != e2->keylen) {
                if (e1->keylen < e2->keylen)
                        ret = -1;
                else if (e1->keylen > e2->keylen)
                        ret = 1;
        } else
                ret = memcmp (e1->key, e2->key, e1->keylen);

        return ret;
}

bst_entry_t *
bstree_init_entry (void *data, void *key, int keylen)
{
        int             ret = -1;
        bst_entry_t *entry = NULL;

        if ((!data) || (!key))
                return NULL;

        entry = (bst_entry_t *)calloc(1, sizeof(struct bst_entry));

        //data使用外面的内存
        entry->data = data;
        entry->key = calloc (keylen, sizeof (char));
        if (!entry->key) {
                goto free_entry;
        }

        memcpy (entry->key, key, keylen);
        entry->keylen = keylen;

        ret = 0;
free_entry:
        if (ret == -1) {
                free (entry);
                entry = NULL;
        }

        return entry;
}

void
bstree_deinit_entry (bst_entry_t *entry)
{

        if (!entry)
                return;

        free (entry->key);

        return;
}


int
bstree_insert_entry (bstree_table_t *tbl, bst_entry_t *entry)
{
        int  ret = 0;

        if ((!tbl) || (!entry))
                return -1;

        LOCK (&tbl->tablelock);
        // 还是使用 bst_insert
        if (!bst_insert (tbl->table, (void *)entry)) {
                LOG_PRINT(D_LOG_ERR, "Failed to insert"
                        " entry");
                ret = -1;
        }
        UNLOCK (&tbl->tablelock);

        return ret;
}


int
bstree_insert (bstree_table_t *tbl, void *data, void *key, int keylen)
{
        bst_entry_t         *entry = NULL;
        int                     ret = -1;

        if ((!tbl) || (!data) || (!key))
                return -1;

        entry = bstree_init_entry (data, key, keylen);
        if (!entry) {
                LOG_PRINT(D_LOG_ERR, "Failed to init entry");
                goto err;
        }

        ret = bstree_insert_entry (tbl, entry);

        if (ret == -1) {
                LOG_PRINT(D_LOG_ERR, "Failed to insert entry");
                bstree_deinit_entry ( entry);
        }

err:
        return ret;
}


void *
bstree_get (bstree_table_t *tbl, void *key, int keylen)
{
        bst_entry_t                 *entry = NULL;
        bst_entry_t                 searchentry = {0, };

        if ((!tbl) || (!key))
                return NULL;

        searchentry.key = key;
        searchentry.keylen = keylen;
        
        LOCK (&tbl->tablelock);
        entry = bst_find (tbl->table, &searchentry);
        UNLOCK (&tbl->tablelock);

        if (!entry)
                return NULL;

        return entry->data;
}


void *
bstree_remove (bstree_table_t *tbl, void *key, int keylen)
{
        bst_entry_t         *entry = NULL;
        bst_entry_t         searchentry = {0, };
        void                    *dataref = NULL;

        if ((!tbl) || (!key))
                return NULL;


        searchentry.key = key;
        searchentry.keylen = keylen;

        LOCK (&tbl->tablelock);
        entry = bst_delete (tbl->table, &searchentry);
        UNLOCK (&tbl->tablelock);

        if (!entry)
                return NULL;
        // 内存要自己释放
        free (entry->key);
        dataref = entry->data;

        // 内存要自己释放 
        free(entry);

        // 数据返回给上层
        return dataref;
}


int32_t main(int32_t argc, char **argv)
{
    struct bstree_table my_table = {0};
    
    my_table.table = bst_create ((bst_comparison_func *)bstree_comparator, NULL, NULL);

    return 0;

}

#ifdef __cplusplus
}
#endif
