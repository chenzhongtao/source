/*
 * hash_map_value_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);
    binary_function_t bfun_vc = NULL;
    bool_t b_result = false;
    hash_map_iterator_t it_hm1;
    hash_map_iterator_t it_hm2;

    if(phm_hm1 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    pair_init(ppr_hm);
    hash_map_init_ex(phm_hm1, 100, NULL, fun_less_int);

    pair_make(ppr_hm, 1, 10);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 2, 5);
    hash_map_insert(phm_hm1, ppr_hm);

    it_hm1 = hash_map_find(phm_hm1, 1);
    it_hm2 = hash_map_find(phm_hm1, 2);
    bfun_vc = hash_map_value_comp(phm_hm1);

    (*bfun_vc)(iterator_get_pointer(it_hm1), iterator_get_pointer(it_hm2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_hm2), iterator_get_pointer(it_hm1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }

    pair_destroy(ppr_hm);
    hash_map_destroy(phm_hm1);

    return 0;
}
