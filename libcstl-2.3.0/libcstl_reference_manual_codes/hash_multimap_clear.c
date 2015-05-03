/*
 * hash_multimap_clear.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    pair_t* ppr_hmm = create_pair(int, int);

    if(phmm_hmm1 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    pair_init(ppr_hmm);

    pair_make(ppr_hmm, 1, 1);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 2, 4);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);

    printf("The size of the hash_multimap is initially %d.\n", hash_multimap_size(phmm_hmm1));

    hash_multimap_clear(phmm_hmm1);

    printf("The size of the hash_multimap after clearing is %d.\n", hash_multimap_size(phmm_hmm1));

    hash_multimap_destroy(phmm_hmm1);
    pair_destroy(ppr_hmm);

    return 0;
}
