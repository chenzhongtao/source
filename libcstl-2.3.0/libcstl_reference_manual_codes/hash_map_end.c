/*
 * hash_map_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_iterator_t it_hm;
    pair_t* ppr_hm = create_pair(int, int);

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

    it_hm = iterator_prev(hash_map_end(phm_hm1));
    printf("The value of last element of hm1 is (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));

    hash_map_erase_pos(phm_hm1, it_hm);

    it_hm = iterator_prev(hash_map_end(phm_hm1));
    printf("The value of last element of hm1 is now (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));

    hash_map_destroy(phm_hm1);
    pair_destroy(ppr_hm);

    return 0;
}
