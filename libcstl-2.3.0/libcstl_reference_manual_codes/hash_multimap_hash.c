/*
 * hash_multimap_hash.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

static void hash_func(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    hash_multimap_init_ex(phmm_hmm2, 100, hash_func, NULL);

    if(hash_multimap_hash(phmm_hmm1) == hash_func)
    {
        printf("The hash function of hash_multimap hmm1 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_multimap hmm1 is not hash_func.\n");
    }

    if(hash_multimap_hash(phmm_hmm2) == hash_func)
    {
        printf("The hash function of hash_multimap hmm2 is hash_func.\n");
    }
    else
    {
        printf("The hash function of hash_multimap hmm2 is not hash_func.\n");
    }

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);

    return 0;
}

static void hash_func(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)pair_first((pair_t*)cpv_input);
}
