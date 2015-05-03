/*
 * hash_map_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);
    range_t r_hm;

    if(phm_hm1 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    pair_init(ppr_hm);

    pair_make(ppr_hm, 1, 10);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 2, 20);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 3, 30);
    hash_map_insert(phm_hm1, ppr_hm);

    r_hm = hash_map_equal_range(phm_hm1, 2);
    printf("The lower bound of the element with a key of 2 in the hash_map hm1 is: (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(r_hm.it_begin)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(r_hm.it_begin)));
    printf("The upper bound of the element with a key of 2 in the hash_map hm1 is: (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(r_hm.it_end)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(r_hm.it_end)));

    r_hm = hash_map_equal_range(phm_hm1, 4);
    if(iterator_equal(r_hm.it_begin, hash_map_end(phm_hm1)) &&
       iterator_equal(r_hm.it_end, hash_map_end(phm_hm1)))
    {
        printf("The hash_map hm1 doesn't have an element with a key less than 4.\n");
    }
    else
    {
        printf("The element of hash_map hm1 with a key >= 4 is (%d, %d).\n",
            *(int*)pair_first((pair_t*)iterator_get_pointer(r_hm.it_begin)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(r_hm.it_begin)));
    }

    hash_map_destroy(phm_hm1);
    pair_destroy(ppr_hm);

    return 0;
}
