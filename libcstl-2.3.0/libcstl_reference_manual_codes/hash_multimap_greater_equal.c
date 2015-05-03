/*
 * hash_multimap_greater_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm3 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm4 = create_hash_multimap(int, int);
    pair_t* ppr_hmm = create_pair(int, int);
    int i = 0;

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL || phmm_hmm3 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    hash_multimap_init(phmm_hmm2);
    hash_multimap_init(phmm_hmm3);
    hash_multimap_init(phmm_hmm4);
    pair_init(ppr_hmm);

    for(i = 1; i < 3; ++i)
    {
        pair_make(ppr_hmm, i, i);
        hash_multimap_insert(phmm_hmm1, ppr_hmm);
        hash_multimap_insert(phmm_hmm4, ppr_hmm);
        pair_make(ppr_hmm, i, i * i);
        hash_multimap_insert(phmm_hmm2, ppr_hmm);
        pair_make(ppr_hmm, i, i - 1);
        hash_multimap_insert(phmm_hmm3, ppr_hmm);
    }

    if(hash_multimap_greater_equal(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap hmm1 is greater than or equal to the hash_multimap hmm2.\n");
    }
    else
    {
        printf("The hash_multimap hmm1 is less than the hash_multimap hmm2.\n");
    }

    if(hash_multimap_greater_equal(phmm_hmm1, phmm_hmm3))
    {
        printf("The hash_multimap hmm1 is greater than or equal to the hash_multimap hmm3.\n");
    }
    else
    {
        printf("The hash_multimap hmm1 is less than the hash_multimap hmm3.\n");
    }

    if(hash_multimap_greater_equal(phmm_hmm1, phmm_hmm4))
    {
        printf("The hash_multimap hmm1 is greater than or equal to the hash_multimap hmm4.\n");
    }
    else
    {
        printf("The hash_multimap hmm1 is less than the hash_multimap hmm4.\n");
    }

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    hash_multimap_destroy(phmm_hmm3);
    hash_multimap_destroy(phmm_hmm4);
    pair_destroy(ppr_hmm);

    return 0;
}
