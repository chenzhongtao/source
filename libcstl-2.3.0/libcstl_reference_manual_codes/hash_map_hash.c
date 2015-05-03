/*
 * hash_map_hash.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

static void hash_func(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_t* phm_hm2 = create_hash_map(int, int);

    if(phm_hm1 == NULL || phm_hm2 == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    hash_map_init_ex(phm_hm2, 100, hash_func, NULL);

    if(hash_map_hash(phm_hm1) == hash_func)
    {
        printf("The hash function of hash_map hm1 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_map hm1 is not hash_func.\n");
    }

    if(hash_map_hash(phm_hm2) == hash_func)
    {
        printf("The hash function of hash_map hm2 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_map hm2 is not hash_func.\n");
    }

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);

    return 0;
}

static void hash_func(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)pair_first((pair_t*)cpv_input);
}
