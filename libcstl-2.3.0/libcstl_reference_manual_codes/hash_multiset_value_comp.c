/*
 * hash_multiset_value_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_t* phms_hms2 = create_hash_multiset(int);
    binary_function_t bfun_vc = NULL;
    int n_first = 2;
    int n_second = 3;
    bool_t b_result = false;

    if(phms_hms1 == NULL || phms_hms2 == NULL)
    {
        return -1;
    }

    hash_multiset_init_ex(phms_hms1, 0, NULL, fun_less_int);
    hash_multiset_init_ex(phms_hms2, 0, NULL, fun_greater_int);

    bfun_vc = hash_multiset_value_comp(phms_hms1);
    (*bfun_vc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_vc)(2, 3) returns value of true, where bfun_vc is the compare function of hs1.\n");
    }
    else
    {
        printf("(*bfun_vc)(2, 3) returns value of false, where bfun_vc is the compare function of hs1.\n");
    }

    bfun_vc = hash_multiset_value_comp(phms_hms2);
    (*bfun_vc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_vc)(2, 3) returns value of true, where bfun_vc is the compare function of hs2.\n");
    }
    else
    {
        printf("(*bfun_vc)(2, 3) returns value of false, where bfun_vc is the compare function of hs2.\n");
    }

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);

    return 0;
}
