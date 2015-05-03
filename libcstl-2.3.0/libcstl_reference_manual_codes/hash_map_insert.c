/*
 * hash_map_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_t* phm_hm2 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);
    hash_map_iterator_t it_hm;

    if(phm_hm1 == NULL || phm_hm2 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    hash_map_init(phm_hm2);
    pair_init(ppr_hm);

    pair_make(ppr_hm, 1, 10);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 2, 20);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 3, 30);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 4, 40);
    hash_map_insert(phm_hm1, ppr_hm);

    printf("The original elements of hm1 are:");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    pair_make(ppr_hm, 1, 10);
    it_hm = hash_map_insert(phm_hm1, ppr_hm);
    if(iterator_not_equal(it_hm, hash_map_end(phm_hm1)))
    {
        printf("The element (1, 10) was inserted in hm1 successfully.\n");
    }
    else
    {
        printf("The element (1, 10) alread exists in hm1.\n");
    }

    pair_make(ppr_hm, 10, 100);
    hash_map_insert(phm_hm2, ppr_hm);
    hash_map_insert_range(phm_hm2, iterator_next(hash_map_begin(phm_hm1)),
        iterator_prev(hash_map_end(phm_hm1)));
    printf("After the insertions, the elements of hm2 are:");
    for(it_hm = hash_map_begin(phm_hm2);
        !iterator_equal(it_hm, hash_map_end(phm_hm2));
        it_hm = iterator_next(it_hm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    pair_destroy(ppr_hm);

    return 0;
}
