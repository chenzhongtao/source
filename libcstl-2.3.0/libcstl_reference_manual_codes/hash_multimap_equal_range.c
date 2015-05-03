/*
 * hash_multimap_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    pair_t* ppr_hmm = create_pair(int, int);
    range_t r_hmm;

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

    r_hmm = hash_multimap_equal_range(phmm_hmm1, 2);
    printf("The lower bound of the element with a key of 2 in the hash_multimap hmm1 is: (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(r_hmm.it_begin)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(r_hmm.it_begin)));
    printf("The upper bound of the element with a key of 2 in the hash_multimap hmm1 is: (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(r_hmm.it_end)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(r_hmm.it_end)));

    r_hmm = hash_multimap_equal_range(phmm_hmm1, 4);
    if(iterator_equal(r_hmm.it_begin, hash_multimap_end(phmm_hmm1)) &&
       iterator_equal(r_hmm.it_end, hash_multimap_end(phmm_hmm1)))
    {
        printf("The hash_multimap hmm1 doesn't have an element with a key less than 4.\n");
    }
    else
    {
        printf("The element of hash_multimap hmm1 with a key >= 4 is (%d, %d).\n",
            *(int*)pair_first((pair_t*)iterator_get_pointer(r_hmm.it_begin)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(r_hmm.it_begin)));
    }

    hash_multimap_destroy(phmm_hmm1);
    pair_destroy(ppr_hmm);

    return 0;
}
