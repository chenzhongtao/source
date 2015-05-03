/*
 * hash_multimap_count.c
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

    pair_init(ppr_hmm);
    hash_multimap_init(phmm_hmm1);

    pair_make(ppr_hmm, 1, 1);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 2, 1);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 1, 4);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 2, 1);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);

    /* Key must be unique in hash_multimap, so duplicates are ignored */
    printf("The number of elements in hmm1 with a sort key of 1 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 1));
    printf("The number of elements in hmm1 with a sort key of 2 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 2));
    printf("The number of elements in hmm1 with a sort key of 3 is: %d.\n",
        hash_multimap_count(phmm_hmm1, 3));

    pair_destroy(ppr_hmm);
    hash_multimap_destroy(phmm_hmm1);

    return 0;
}
