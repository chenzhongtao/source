/*
 * hash_map_count.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);

    if(phm_hm1 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    pair_init(ppr_hm);
    hash_map_init(phm_hm1);

    pair_make(ppr_hm, 1, 1);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 2, 1);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 1, 4);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 2, 1);
    hash_map_insert(phm_hm1, ppr_hm);

    /* Key must be unique in hash_map, so duplicates are ignored */
    printf("The number of elements in hm1 with a sort key of 1 is: %d.\n",
        hash_map_count(phm_hm1, 1));
    printf("The number of elements in hm1 with a sort key of 2 is: %d.\n",
        hash_map_count(phm_hm1, 2));
    printf("The number of elements in hm1 with a sort key of 3 is: %d.\n",
        hash_map_count(phm_hm1, 3));

    pair_destroy(ppr_hm);
    hash_map_destroy(phm_hm1);

    return 0;
}
