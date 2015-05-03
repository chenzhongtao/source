/*
 * hash_multimap_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm3 = create_hash_multimap(int, int);
    pair_t* ppr_hmm = create_pair(int, int);
    hash_multimap_iterator_t it_hmm;
    size_t t_count = 0;
    int i = 0;

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL || phmm_hmm3 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    hash_multimap_init(phmm_hmm2);
    hash_multimap_init(phmm_hmm3);
    pair_init(ppr_hmm);

    for(i = 1; i < 5; ++i)
    {
        pair_make(ppr_hmm, i, i);
        hash_multimap_insert(phmm_hmm1, ppr_hmm);
        pair_make(ppr_hmm, i, i * i);
        hash_multimap_insert(phmm_hmm2, ppr_hmm);
        pair_make(ppr_hmm, i, i - 1);
        hash_multimap_insert(phmm_hmm3, ppr_hmm);
    }

    /* The first function removes an element at given position */
    hash_multimap_erase_pos(phmm_hmm1, iterator_next(hash_multimap_begin(phmm_hmm1)));
    printf("After the second element is deleted, the hash_multimap hmm1 is:");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    /* The second function remove elements in the range [first, last) */
    hash_multimap_erase_range(phmm_hmm2, iterator_next(hash_multimap_begin(phmm_hmm2)),
        iterator_prev(hash_multimap_end(phmm_hmm2)));
    printf("After the middle two elements are deleted, the hash_multimap hmm2 is:");
    for(it_hmm = hash_multimap_begin(phmm_hmm2);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm2));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    /* The third function removes elements with a given key */
    t_count = hash_multimap_erase(phmm_hmm3, 2);
    printf("After the element with a key of 2 is deleted, the hash_multimap hmm3 is:");
    for(it_hmm = hash_multimap_begin(phmm_hmm3);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm3));
        it_hmm = iterator_next(it_hmm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");
    /* The third function returns the number of elements returned */
    printf("The number of elements removed from hmm3 is %d.\n", t_count);

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    hash_multimap_destroy(phmm_hmm3);
    pair_destroy(ppr_hmm);

    return 0;
}
