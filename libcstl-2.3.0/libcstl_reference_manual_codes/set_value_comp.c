/*
 * set_value_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cset.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    set_t* pset_s1 = create_set(int);
    set_t* pset_s2 = create_set(int);
    binary_function_t bfun_vl = NULL;
    int n_element1 = 0;
    int n_element2 = 0;
    bool_t b_result = false;

    if(pset_s1 == NULL || pset_s2 == NULL)
    {
        return -1;
    }

    set_init(pset_s1);

    bfun_vl = set_value_comp(pset_s1);
    n_element1 = 2;
    n_element2 = 3;
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s1.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s1.\n");
    }

    set_destroy(pset_s1);

    set_init_ex(pset_s2, fun_greater_int);

    bfun_vl = set_value_comp(pset_s2);
    (*bfun_vl)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_vl)(2, 3) returns value of true, where bfun_vl is the function of s2.\n");
    }
    else
    {
        printf("(*bfun_vl)(2, 3) returns value of false, where bfun_vl is the function of s2.\n");
    }

    set_destroy(pset_s2);

    return 0;
}
