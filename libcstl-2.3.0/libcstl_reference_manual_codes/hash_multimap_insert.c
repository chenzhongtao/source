/*
 * hash_multimap_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);
    pair_t* ppr_hmm = create_pair(int, int);
    hash_multimap_iterator_t it_hmm;

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    hash_multimap_init(phmm_hmm2);
    pair_init(ppr_hmm);

    pair_make(ppr_hmm, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 2, 20);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 3, 30);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 4, 40);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);

    printf("The original elements of hmm1 are:");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    pair_make(ppr_hmm, 1, 10);
    it_hmm = hash_multimap_insert(phmm_hmm1, ppr_hmm);
    if(iterator_not_equal(it_hmm, hash_multimap_end(phmm_hmm1)))
    {
        printf("The element (1, 10) was inserted in hmm1 successfully.\n");
    }
    else
    {
        printf("The element (1, 10) alread exists in hmm1.\n");
    }

    pair_make(ppr_hmm, 10, 100);
    hash_multimap_insert(phmm_hmm2, ppr_hmm);
    hash_multimap_insert_range(phmm_hmm2, iterator_next(hash_multimap_begin(phmm_hmm1)),
        iterator_prev(hash_multimap_end(phmm_hmm1)));
    printf("After the insertions, the elements of hmm2 are:");
    for(it_hmm = hash_multimap_begin(phmm_hmm2);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm2));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    pair_destroy(ppr_hmm);

    return 0;
}
