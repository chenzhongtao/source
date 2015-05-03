/*
 * hash_multimap_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <string.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

static void _default_hash(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    hash_multimap_t* phmm_hmm0 = create_hash_multimap(char*, int);
    hash_multimap_t* phmm_hmm1 = create_hash_multimap(char*, int);
    hash_multimap_t* phmm_hmm2 = create_hash_multimap(char*, int);
    hash_multimap_t* phmm_hmm3 = create_hash_multimap(char*, int);
    hash_multimap_t* phmm_hmm4 = create_hash_multimap(char*, int);
    hash_multimap_t* phmm_hmm5 = create_hash_multimap(char*, int);
    hash_multimap_iterator_t it_hmm;
    pair_t* ppr_hmm = create_pair(char*, int);

    if(phmm_hmm0 == NULL || phmm_hmm1 == NULL || phmm_hmm2 == NULL ||
       phmm_hmm3 == NULL || phmm_hmm4 == NULL || phmm_hmm5 == NULL ||
       ppr_hmm == NULL)
    {
        return -1;
    }

    pair_init(ppr_hmm);

    /* Create an empty hash_multimap hmm0 of key type string */
    hash_multimap_init(phmm_hmm0);

    /*
     * Create an empty hash_multimap hmm1 with the key comparison
     * function of less than, than insert 4 elements
     */
    hash_multimap_init_ex(phmm_hmm1, 0, _default_hash, fun_less_cstr);
    pair_make(ppr_hmm, "one", 0);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, "two", 10);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, "three", 20);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, "four", 30);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);
    pair_make(ppr_hmm, "five", 40);
    hash_multimap_insert(phmm_hmm1, ppr_hmm);

    /*
     * Create an empty hash_multimap hmm2 with the key comparison
     * function of greater than, then insert 2 elements
     */
    hash_multimap_init_ex(phmm_hmm2, 100, _default_hash, fun_greater_cstr);
    pair_make(ppr_hmm, "one", 10);
    hash_multimap_insert(phmm_hmm2, ppr_hmm);
    pair_make(ppr_hmm, "two", 20);
    hash_multimap_insert(phmm_hmm2, ppr_hmm);

    /* Create a copy, hash_multimap hmm3, of hash_multimap hmm1 */
    hash_multimap_init_copy(phmm_hmm3, phmm_hmm1);

    /* Create a hash_multimap hmm4 by coping the range hmm1[first, last) */
    hash_multimap_init_copy_range(phmm_hmm4,
        iterator_advance(hash_multimap_begin(phmm_hmm1), 2), hash_multimap_end(phmm_hmm1));

    /* 
     * Create a hash_multimap hmm5 by copying the range hmm3 [first, last)
     * and with the key comparison function of less than
     */
    hash_multimap_init_copy_range_ex(phmm_hmm5, hash_multimap_begin(phmm_hmm3),
        hash_multimap_end(phmm_hmm3), 100, _default_hash, fun_less_cstr);

    printf("hmm1 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm1);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm1));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    printf("hmm2 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm2);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm2));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    printf("hmm3 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm3);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm3));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    printf("hmm4 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm4);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm4));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    printf("hmm5 =");
    for(it_hmm = hash_multimap_begin(phmm_hmm5);
        !iterator_equal(it_hmm, hash_multimap_end(phmm_hmm5));
        it_hmm = iterator_next(it_hmm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hmm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hmm)));
    }
    printf("\n");

    hash_multimap_destroy(phmm_hmm0);
    hash_multimap_destroy(phmm_hmm1);
    hash_multimap_destroy(phmm_hmm2);
    hash_multimap_destroy(phmm_hmm3);
    hash_multimap_destroy(phmm_hmm4);
    hash_multimap_destroy(phmm_hmm5);
    pair_destroy(ppr_hmm);

    return 0;
}

static void _default_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = strlen((char*)pair_first((pair_t*)cpv_input));
}
