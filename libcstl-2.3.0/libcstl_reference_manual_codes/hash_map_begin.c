/*
 * hash_map_begin.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);
    hash_map_iterator_t it_hm;

    if(phm_hm1 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    pair_init(ppr_hm);

    pair_make(ppr_hm, 0, 0);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 1, 1);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 2, 4);
    hash_map_insert(phm_hm1, ppr_hm);

    it_hm = hash_map_begin(phm_hm1);
    printf("The first element of hm1 is (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));

    hash_map_erase_pos(phm_hm1, hash_map_begin(phm_hm1));

    it_hm = hash_map_begin(phm_hm1);
    printf("The first element of hm1 is now (%d, %d).\n",
        *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
        *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));

    hash_map_destroy(phm_hm1);
    pair_destroy(ppr_hm);

    return 0;
}
