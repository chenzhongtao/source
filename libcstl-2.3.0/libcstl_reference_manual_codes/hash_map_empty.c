/*
 * hash_map_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_t* phm_hm2 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);

    if(phm_hm1 == NULL || phm_hm2 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    hash_map_init(phm_hm2);
    pair_init(ppr_hm);

    pair_make(ppr_hm, 1, 1);
    hash_map_insert(phm_hm1, ppr_hm);

    if(hash_map_empty(phm_hm1))
    {
        printf("The hash_map hm1 is empty.\n");
    }
    else
    {
        printf("The hash_map hm1 is not empty.\n");
    }

    if(hash_map_empty(phm_hm2))
    {
        printf("The hash_map hm2 is empty.\n");
    }
    else
    {
        printf("The hash_map hm2 is not empty.\n");
    }

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    pair_destroy(ppr_hm);

    return 0;
}
