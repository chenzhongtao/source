/*
 * hash_map_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <string.h>
#include <cstl/chash_map.h>
#include <cstl/cfunctional.h>

static void _default_hash(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm0 = create_hash_map(char*, int);
    hash_map_t* phm_hm1 = create_hash_map(char*, int);
    hash_map_t* phm_hm2 = create_hash_map(char*, int);
    hash_map_t* phm_hm3 = create_hash_map(char*, int);
    hash_map_t* phm_hm4 = create_hash_map(char*, int);
    hash_map_t* phm_hm5 = create_hash_map(char*, int);
    hash_map_iterator_t it_hm;
    pair_t* ppr_hm = create_pair(char*, int);

    if(phm_hm0 == NULL || phm_hm1 == NULL || phm_hm2 == NULL ||
       phm_hm3 == NULL || phm_hm4 == NULL || phm_hm5 == NULL ||
       ppr_hm == NULL)
    {
        return -1;
    }

    pair_init(ppr_hm);

    /* Create an empty hash_map hm0 of key type string */
    hash_map_init(phm_hm0);

    /*
     * Create an empty hash_map hm1 with the key comparison
     * function of less than, than insert 4 elements
     */
    hash_map_init_ex(phm_hm1, 0, _default_hash, fun_less_cstr);
    pair_make(ppr_hm, "one", 0);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, "two", 10);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, "three", 20);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, "four", 30);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, "five", 40);
    hash_map_insert(phm_hm1, ppr_hm);

    /*
     * Create an empty hash_map hm2 with the key comparison
     * function of greater than, then insert 2 elements
     */
    hash_map_init_ex(phm_hm2, 100, _default_hash, fun_greater_cstr);
    pair_make(ppr_hm, "one", 10);
    hash_map_insert(phm_hm2, ppr_hm);
    pair_make(ppr_hm, "two", 20);
    hash_map_insert(phm_hm2, ppr_hm);

    /* Create a copy, hash_map hm3, of hash_map hm1 */
    hash_map_init_copy(phm_hm3, phm_hm1);

    /* Create a hash_map hm4 by coping the range hm1[first, last) */
    hash_map_init_copy_range(phm_hm4,
        iterator_advance(hash_map_begin(phm_hm1), 2), hash_map_end(phm_hm1));

    /* 
     * Create a hash_map hm5 by copying the range hm3 [first, last)
     * and with the key comparison function of less than
     */
    hash_map_init_copy_range_ex(phm_hm5, hash_map_begin(phm_hm3),
        hash_map_end(phm_hm3), 100, _default_hash, fun_less_cstr);

    printf("hm1 =");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("hm2 =");
    for(it_hm = hash_map_begin(phm_hm2);
        !iterator_equal(it_hm, hash_map_end(phm_hm2));
        it_hm = iterator_next(it_hm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("hm3 =");
    for(it_hm = hash_map_begin(phm_hm3);
        !iterator_equal(it_hm, hash_map_end(phm_hm3));
        it_hm = iterator_next(it_hm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("hm4 =");
    for(it_hm = hash_map_begin(phm_hm4);
        !iterator_equal(it_hm, hash_map_end(phm_hm4));
        it_hm = iterator_next(it_hm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("hm5 =");
    for(it_hm = hash_map_begin(phm_hm5);
        !iterator_equal(it_hm, hash_map_end(phm_hm5));
        it_hm = iterator_next(it_hm))
    {
        printf("(%s, %d) ",
            (char*)pair_first((pair_t*)iterator_get_pointer(it_hm)),
            *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    hash_map_destroy(phm_hm0);
    hash_map_destroy(phm_hm1);
    hash_map_destroy(phm_hm2);
    hash_map_destroy(phm_hm3);
    hash_map_destroy(phm_hm4);
    hash_map_destroy(phm_hm5);
    pair_destroy(ppr_hm);

    return 0;
}

static void _default_hash(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = strlen((char*)pair_first((pair_t*)cpv_input));
}
