/*
 * hash_map_less_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_t* phm_hm2 = create_hash_map(int, int);
    hash_map_t* phm_hm3 = create_hash_map(int, int);
    hash_map_t* phm_hm4 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);
    int i = 0;

    if(phm_hm1 == NULL || phm_hm2 == NULL || phm_hm3 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    hash_map_init(phm_hm2);
    hash_map_init(phm_hm3);
    hash_map_init(phm_hm4);
    pair_init(ppr_hm);

    for(i = 1; i < 3; ++i)
    {
        pair_make(ppr_hm, i, i);
        hash_map_insert(phm_hm1, ppr_hm);
        hash_map_insert(phm_hm4, ppr_hm);
        pair_make(ppr_hm, i, i * i);
        hash_map_insert(phm_hm2, ppr_hm);
        pair_make(ppr_hm, i, i - 1);
        hash_map_insert(phm_hm3, ppr_hm);
    }

    if(hash_map_less_equal(phm_hm1, phm_hm2))
    {
        printf("The hash_map hm1 is less than or equal to the hash_map hm2.\n");
    }
    else
    {
        printf("The hash_map hm1 is greater than the hash_map hm2.\n");
    }

    if(hash_map_less_equal(phm_hm1, phm_hm3))
    {
        printf("The hash_map hm1 is less than or equal to the hash_map hm3.\n");
    }
    else
    {
        printf("The hash_map hm1 is greater than the hash_map hm3.\n");
    }

    if(hash_map_less_equal(phm_hm1, phm_hm4))
    {
        printf("The hash_map hm1 is less than or equal to the hash_map hm4.\n");
    }
    else
    {
        printf("The hash_map hm1 is greater than the hash_map hm4.\n");
    }

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    hash_map_destroy(phm_hm3);
    hash_map_destroy(phm_hm4);
    pair_destroy(ppr_hm);

    return 0;
}
