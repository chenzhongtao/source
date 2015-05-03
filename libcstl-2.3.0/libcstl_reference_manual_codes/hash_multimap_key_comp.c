/*
 * hash_multimap_key_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(int, int);
    binary_function_t bfun_kc = NULL;
    int n_first = 2;
    int n_second = 3;
    bool_t b_result = false;

    if(phmm_hmm1 == NULL || phmm_hmm2 == NULL)
    {
        return -1;
    }

    hash_multimap_init_ex(phmm_hmm1, 0, NULL, fun_less_int);
    hash_multimap_init_ex(phmm_hmm2, 0, NULL, fun_greater_int);

    bfun_kc = hash_multimap_key_comp(phmm_hmm1);
    (*bfun_kc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the compare function of hmm1.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the compare function of hmm1.\n");
    }

    bfun_kc = hash_multimap_key_comp(phmm_hmm2);
    (*bfun_kc)(&n_first, &n_second, &b_result);
    if(b_result)
    {
        printf("(*bfun_kc)(2, 3) returns value of true, where bfun_kc is the compare function of hmm2.\n");
    }
    else
    {
        printf("(*bfun_kc)(2, 3) returns value of false, where bfun_kc is the compare function of hmm2.\n");
    }

    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);

    return 0;
}
