/*
 * hash_map_erase.c
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
    size_t t_count = 0;
    int i = 0;

    if(phm_hm1 == NULL || phm_hm2 == NULL || phm_hm3 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    hash_map_init(phm_hm2);
    hash_map_init(phm_hm3);
    pair_init(ppr_hm);

    for(i = 1; i < 5; ++i)
    {
        pair_make(ppr_hm, i, i);
        hash_map_insert(phm_hm1, ppr_hm);
        pair_make(ppr_hm, i, i * i);
        hash_map_insert(phm_hm2, ppr_hm);
        pair_make(ppr_hm, i, i - 1);
        hash_map_insert(phm_hm3, ppr_hm);
    }

    /* The first function removes an element at given position */
    hash_map_erase_pos(phm_hm1, iterator_next(hash_map_begin(phm_hm1)));
    printf("After the second element is deleted, the hash_map hm1 is:");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    /* The second function remove elements in the range [first, last) */
    hash_map_erase_range(phm_hm2, iterator_next(hash_map_begin(phm_hm2)),
        iterator_prev(hash_map_end(phm_hm2)));
    printf("After the middle two elements are deleted, the hash_map hm2 is:");
    for(it_hm = hash_map_begin(phm_hm2);
        !iterator_equal(it_hm, hash_map_end(phm_hm2));
        it_hm = iterator_next(it_hm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    /* The third function removes elements with a given key */
    t_count = hash_map_erase(phm_hm3, 2);
    printf("After the element with a key of 2 is deleted, the hash_map hm3 is:");
    for(it_hm = hash_map_begin(phm_hm3);
        !iterator_equal(it_hm, hash_map_end(phm_hm3));
        it_hm = iterator_next(it_hm))
    {
        printf(" (%d, %d)",
            *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");
    /* The third function returns the number of elements returned */
    printf("The number of elements removed from hm3 is %d.\n", t_count);

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    hash_map_destroy(phm_hm3);
    pair_destroy(ppr_hm);

    return 0;
}
