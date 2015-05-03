/*
 * hash_multimap_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);
    pair_t* ppr_hmm = create_pair(int, int);

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    hash_multimap_init(phmm_hmm2);
    pair_init(ppr_hmm);

    pair_make(ppr_hmm, 1, 1);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);

    if(hash_multimap_empty(phmm_hmm1))
    {
        printf("The hash_multimap hmm1 is empty.\n");
    }
    else
    {
        printf("The hash_multimap hmm1 is not empty.\n");
    }

    if(hash_multimap_empty(phmm_hmm2))
    {
        printf("The hash_multimap hmm2 is empty.\n");
    }
    else
    {
        printf("The hash_multimap hmm2 is not empty.\n");
    }

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    pair_destroy(ppr_hmm);

    return 0;
}
