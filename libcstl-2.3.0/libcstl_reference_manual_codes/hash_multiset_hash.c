/*
 * hash_multiset_hash.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

static void hash_func(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_t* phms_hms2 = create_hash_multiset(int);

    if(phms_hms1 == NULL || phms_hms2 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);
    hash_multiset_init_ex(phms_hms2, 100, hash_func, NULL);

    if(hash_multiset_hash(phms_hms1) == hash_func)
    {
        printf("The hash function of hash_multiset hs1 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_multiset hs1 is not hash_func.\n");
    }

    if(hash_multiset_hash(phms_hms2) == hash_func)
    {
        printf("The hash function of hash_multiset hs2 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_multiset hs2 is not hash_func.\n");
    }

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);

    return 0;
}

static void hash_func(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_input;
}
