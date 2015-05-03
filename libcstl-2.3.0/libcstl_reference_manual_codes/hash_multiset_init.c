/*
 * hash_multiset_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>
#include <cstl/cfunctional.h>

static void _hash_function(const void* cpv_input, void* pv_output)
{
    *(size_t*)pv_output = *(int*)cpv_input + 20;
}

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms0 = create_hash_multiset(int);
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_t* phms_hms2 = create_hash_multiset(int);
    hash_multiset_t* phms_hms3 = create_hash_multiset(int);
    hash_multiset_t* phms_hms4 = create_hash_multiset(int);
    hash_multiset_t* phms_hms5 = create_hash_multiset(int);
    hash_multiset_iterator_t it_hs;

    if(phms_hms0 == NULL || phms_hms1 == NULL || phms_hms2 == NULL ||
       phms_hms3 == NULL || phms_hms4 == NULL || phms_hms5 == NULL)
    {
        return -1;
    }

    /* Create an empty hash_multiset hs0 of key type integer */
    hash_multiset_init(phms_hms0);

    /* 
     * Create an empty hash_multiset hs1 with the key comparison
     * function of less than, then insert 4 elements.
     */
    hash_multiset_init_ex(phms_hms1, 10, _hash_function, fun_less_int);
    hash_multiset_insert(phms_hms1, 10);
    hash_multiset_insert(phms_hms1, 20);
    hash_multiset_insert(phms_hms1, 30);
    hash_multiset_insert(phms_hms1, 40);

    /*
     * Create an empty hash_multiset hs2 with the key comparison
     * function of greater than, then insert 2 element.
     */
    hash_multiset_init_ex(phms_hms2, 100, _hash_function, fun_greater_int);
    hash_multiset_insert(phms_hms2, 10);
    hash_multiset_insert(phms_hms2, 20);

    /* Create a copy, hash_multiset hs3, of hash_multiset hs1 */
    hash_multiset_init_copy(phms_hms3, phms_hms1);

    /* Create a hash_multiset hs4 by copying the range hs1[first, last) */
    hash_multiset_init_copy_range(phms_hms4, hash_multiset_begin(phms_hms1),
        iterator_advance(hash_multiset_begin(phms_hms1), 2));

    /* 
     * Create a hash_multiset hs5 by copying the range hs3[first, last)
     * and with the key comparison function of less than.
     */
    hash_multiset_init_copy_range_ex(phms_hms5, hash_multiset_begin(phms_hms3),
        iterator_next(hash_multiset_begin(phms_hms3)), 100, _hash_function, fun_less_int);

    printf("hs1 =");
    for(it_hs = hash_multiset_begin(phms_hms1);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs2 =");
    for(it_hs = hash_multiset_begin(phms_hms2);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms2));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs3 =");
    for(it_hs = hash_multiset_begin(phms_hms3);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms3));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs4 =");
    for(it_hs = hash_multiset_begin(phms_hms4);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms4));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs5 =");
    for(it_hs = hash_multiset_begin(phms_hms5);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms5));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_multiset_destroy(phms_hms0);
    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);
    hash_multiset_destroy(phms_hms3);
    hash_multiset_destroy(phms_hms4);
    hash_multiset_destroy(phms_hms5);

    return 0;
}
