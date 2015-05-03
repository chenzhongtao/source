/*
 * hash_set_key_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_t* phset_hs2 = create_hash_set(int);
    binary_function_t bfun_kc = NULL;
    int n_first = 2;
    int n_second = 3;
    bool_t b_result = false;

    if(phset_hs1 == NULL || phset_hs2 == NULL)
    {
        return -1;
    }

    hash_set_init_ex(phset_hs1, 0, NULL, fun_less_int);
    hash_set_init_ex(phset_hs2, 0, NULL, fun_greater_int);

    bfun_kc = hash_set_key_comp(phset_hs1);
    (*bfun_kc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the compare function of hs1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the compare function of hs1.\n");
    }

    bfun_kc = hash_set_key_comp(phset_hs2);
    (*bfun_kc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the compare function of hs2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the compare function of hs2.\n");
    }

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);

    return 0;
}
