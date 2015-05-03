/*
 * hash_multimap_value_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(int, int);
    pair_t* ppr_hmm = create_pair(int, int);
    binary_function_t bfun_vc = NULL;
    bool_t b_result = false;
    hash_multimap_iterator_t it_hmm1;
    hash_multimap_iterator_t it_hmm2;

    if(phmm_hmm1 == NULL || ppr_hmm == NULL)
    {
        return -1;
    }

    pair_init(ppr_hmm);
    hash_multimap_init_ex(phmm_hmm1, 100, NULL, fun_less_int);

    pair_make(ppr_hmm, 1, 10);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, 2, 5);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);

    it_hmm1 = hash_multimap_find(phmm_hmm1, 1);
    it_hmm2 = hash_multimap_find(phmm_hmm1, 2);
    bfun_vc = hash_multimap_value_comp(phmm_hmm1);

    (*bfun_vc)(iterator_get_pointer(it_hmm1), iterator_get_pointer(it_hmm2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_hmm2), iterator_get_pointer(it_hmm1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }

    pair_destroy(ppr_hmm);
    hash_multimap_destroy(phmm_hmm1);

    return 0;
}
