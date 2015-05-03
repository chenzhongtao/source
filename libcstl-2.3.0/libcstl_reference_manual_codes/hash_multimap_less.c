/*
 * hash_multimap_less.c
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
    int i = 0;

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL || phmm_hmm3 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    hash_multimap_init(phmm_hmm1);
    hash_multimap_init(phmm_hmm2);
    hash_multimap_init(phmm_hmm3);
    pair_init(ppr_hmm);

    for(i = 1; i < 4; ++i)
    {
        pair_make(ppr_hmm, i, i);
        hash_multimap_insert(phmm_hmm1, ppr_hmm);
        pair_make(ppr_hmm, i, i + 1);
        hash_multimap_insert(phmm_hmm2, ppr_hmm);
        pair_make(ppr_hmm, i + 1, i);
        hash_multimap_insert(phmm_hmm3, ppr_hmm);
    }

    printf("The elements of hash_multimap hmm1 are:");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%d,%d) ",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    printf("The elements of hash_multimap hmm2 are:");
    for(it_hmm = hash_multimap_begin(phmm_hmm2);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm2));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%d,%d) ",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    printf("The elements of hash_multimap hmm3 are:");
    for(it_hmm = hash_multimap_begin(phmm_hmm3);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm3));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%d,%d) ",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    if(hash_multimap_less(phmm_hmm1, phmm_hmm2))
    {
        printf("The hash_multimap hmm1 is less than the hash_multimap hmm2.\n");
    }
    else
    {
        printf("The hash_multimap hmm1 is not less than the hash_multimap hmm2.\n");
    }

    if(hash_multimap_less(phmm_hmm1, phmm_hmm3))
    {
        printf("The hash_multimap hmm1 is less than the hash_multimap hmm3.\n");
    }
    else
    {
        printf("The hash_multimap hmm1 is not less than the hash_multimap hmm3.\n");
    }

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    hash_multimap_destroy(phmm_hmm3);
    pair_destroy(ppr_hmm);

    return 0;
}
