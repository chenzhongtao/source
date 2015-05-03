/*
 * hash_map_clear.c
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

    hash_map_init(phm_hm1);
    pair_init(ppr_hm);

    pair_make(ppr_hm, 1, 1);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 2, 4);
    hash_map_insert(phm_hm1, ppr_hm);

    printf("The size of the hash_map is initially %d.\n", hash_map_size(phm_hm1));

    hash_map_clear(phm_hm1);

    printf("The size of the hash_map after clearing is %d.\n", hash_map_size(phm_hm1));

    hash_map_destroy(phm_hm1);
    pair_destroy(ppr_hm);

    return 0;
}
