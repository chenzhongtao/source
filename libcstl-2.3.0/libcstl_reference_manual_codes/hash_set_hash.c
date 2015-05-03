/*
 * hash_set_hash.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

static void hash_func(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_t* phset_hs2 = create_hash_set(int);

    if(phset_hs1 == NULL || phset_hs2 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);
    hash_set_init_ex(phset_hs2, 100, hash_func, NULL);

    if(hash_set_hash(phset_hs1) == hash_func)
    {
        printf("The hash function of hash_set hs1 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_set hs1 is not hash_func.\n");
    }

    if(hash_set_hash(phset_hs2) == hash_func)
    {
        printf("The hash function of hash_set hs2 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_set hs2 is not hash_func.\n");
    }

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);

    return 0;
}

static void hash_func(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_input;
}
