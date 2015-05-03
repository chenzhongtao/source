/*
 * hash_multimap_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_iterator_t it_hmm;
    pair_t* ppr_hmm = create_pair(int, int);

    if(phmm_hmm1 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    pair_init(ppr_hmm);

    pair_make(ppr_hmm, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);

    it_hmm = iterator_prev(hash_multimap_end(phmm_hmm1));
    printf("The value of last element of hmm1 is (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));

    hash_multimap_erase_pos(phmm_hmm1, it_hmm);

    it_hmm = iterator_prev(hash_multimap_end(phmm_hmm1));
    printf("The value of last element of hmm1 is now (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));

    hash_multimap_destroy(phmm_hmm1);
    pair_destroy(ppr_hmm);

    return 0;
}
