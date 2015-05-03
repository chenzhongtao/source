/*
 * hash_map_key_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    hash_map_t* phm_hm2 = create_hash_map(int, int);
    binary_function_t bfun_kc = NULL;
    int n_first = 2;
    int n_second = 3;
    bool_t b_result = false;

    if(phm_hm1 == NULL || phm_hm2 == NULL)
    {
        return -1;
    }

    hash_map_init_ex(phm_hm1, 0, NULL, fun_less_int);
    hash_map_init_ex(phm_hm2, 0, NULL, fun_greater_int);

    bfun_kc = hash_map_key_comp(phm_hm1);
    (*bfun_kc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the compare function of hm1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the compare function of hm1.\n");
    }

    bfun_kc = hash_map_key_comp(phm_hm2);
    (*bfun_kc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the compare function of hm2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the compare function of hm2.\n");
    }

    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);

    return 0;
}
