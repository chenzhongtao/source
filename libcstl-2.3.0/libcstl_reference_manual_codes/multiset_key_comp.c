/*
 * multiset_key_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multiset_t* pmset_s1 = create_multiset(int);
    multiset_t* pmset_s2 = create_multiset(int);
    binary_function_t bfun_kl = NULL;
    bool_t b_result = false;
    int n_element1 = 0;
    int n_element2 = 0;

    if(pmset_s1 == NULL || pmset_s2 == NULL)
    {
        return -1;
    }

    multiset_init(pmset_s1);

    bfun_kl = multiset_key_comp(pmset_s1);
    n_element1 = 2;
    n_element2 = 3;
    (*bfun_kl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kl)(2, 3) return value of true, where bfun_kl is the function of s1.\n");
    }
    else
    {
        printf("(*bfun_kl)(2, 3) return value of false, where bfun_kl is the function of s1.\n");
    }

    multiset_destroy(pmset_s1);

    multiset_init_ex(pmset_s2, fun_greater_int);

    bfun_kl = multiset_key_comp(pmset_s2);
    (*bfun_kl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kl)(2, 3) return value of true, where bfun_kl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_kl)(2, 3) return value of false, where bfun_kl is the function of s2.\n");
    }

    multiset_destroy(pmset_s2);

    return 0;
}
