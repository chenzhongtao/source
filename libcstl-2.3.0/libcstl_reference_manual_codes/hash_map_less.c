/*
 * hash_map_less.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_t* phm_hm2 = create_hash_map(int, int);
    hash_map_t* phm_hm3 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);
    hash_map_iterator_t it_hm;
    int i = 0;

    if(phm_hm1 == NULL || phm_hm2 == NULL || phm_hm3 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    hash_map_init(phm_hm2);
    hash_map_init(phm_hm3);
    pair_init(ppr_hm);

    for(i = 1; i < 4; ++i)
    {
        pair_make(ppr_hm, i, i);
        hash_map_insert(phm_hm1, ppr_hm);
        pair_make(ppr_hm, i, i + 1);
        hash_map_insert(phm_hm2, ppr_hm);
        pair_make(ppr_hm, i + 1, i);
        hash_map_insert(phm_hm3, ppr_hm);
    }

    printf("The elements of hash_map hm1 are:");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf("(%d,%d) ",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("The elements of hash_map hm2 are:");
    for(it_hm = hash_map_begin(phm_hm2);
        !iterator_equal(it_hm, hash_map_end(phm_hm2));
        it_hm = iterator_next(it_hm))
    {
        printf("(%d,%d) ",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("The elements of hash_map hm3 are:");
    for(it_hm = hash_map_begin(phm_hm3);
        !iterator_equal(it_hm, hash_map_end(phm_hm3));
        it_hm = iterator_next(it_hm))
    {
        printf("(%d,%d) ",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    if(hash_map_less(phm_hm1, phm_hm2))
    {
        printf("The hash_map hm1 is less than the hash_map hm2.\n");
    }
    else
    {
        printf("The hash_map hm1 is not less than the hash_map hm2.\n");
    }

    if(hash_map_less(phm_hm1, phm_hm3))
    {
        printf("The hash_map hm1 is less than the hash_map hm3.\n");
    }
    else
    {
        printf("The hash_map hm1 is not less than the hash_map hm3.\n");
    }

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    hash_map_destroy(phm_hm3);
    pair_destroy(ppr_hm);

    return 0;
}
