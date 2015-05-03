/*
 * multimap_key_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    multimap_t* pmmap_m2 = create_multimap(int, int);
    binary_function_t bfun_kc = NULL;
    int n_element1 = 2;
    int n_element2 = 3;
    bool_t b_result = false;

    if(pmmap_m1 == NULL || pmmap_m2 == NULL)
    {
        return -1;
    }

    multimap_init_ex(pmmap_m1, fun_less_int);

    bfun_kc = multimap_key_comp(pmmap_m1);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m1.\n");
    }

    multimap_destroy(pmmap_m1);

    multimap_init_ex(pmmap_m2, fun_greater_int);

    bfun_kc = multimap_key_comp(pmmap_m2);
    (*bfun_kc)(&n_element1, &n_element2, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the function of m2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the function of m2.\n");
    }

    multimap_destroy(pmmap_m2);

    return 0;
}
