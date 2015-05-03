/*
 * hash_set_init.c
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
    hash_set_t* phset_hs0 = create_hash_set(int);
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_t* phset_hs2 = create_hash_set(int);
    hash_set_t* phset_hs3 = create_hash_set(int);
    hash_set_t* phset_hs4 = create_hash_set(int);
    hash_set_t* phset_hs5 = create_hash_set(int);
    hash_set_iterator_t it_hs;

    if(phset_hs0 == NULL || phset_hs1 == NULL || phset_hs2 == NULL ||
       phset_hs3 == NULL || phset_hs4 == NULL || phset_hs5 == NULL)
    {
        return -1;
    }

    /* Create an empty hash_set hs0 of key type integer */
    hash_set_init(phset_hs0);

    /* 
     * Create an empty hash_set hs1 with the key comparison
     * function of less than, then insert 4 elements.
     */
    hash_set_init_ex(phset_hs1, 10, _hash_function, fun_less_int);
    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    hash_set_insert(phset_hs1, 40);

    /*
     * Create an empty hash_set hs2 with the key comparison
     * function of greater than, then insert 2 element.
     */
    hash_set_init_ex(phset_hs2, 100, _hash_function, fun_greater_int);
    hash_set_insert(phset_hs2, 10);
    hash_set_insert(phset_hs2, 20);

    /* Create a copy, hash_set hs3, of hash_set hs1 */
    hash_set_init_copy(phset_hs3, phset_hs1);

    /* Create a hash_set hs4 by copying the range hs1[first, last) */
    hash_set_init_copy_range(phset_hs4, hash_set_begin(phset_hs1),
        iterator_advance(hash_set_begin(phset_hs1), 2));

    /* 
     * Create a hash_set hs5 by copying the range hs3[first, last)
     * and with the key comparison function of less than.
     */
    hash_set_init_copy_range_ex(phset_hs5, hash_set_begin(phset_hs3),
        iterator_next(hash_set_begin(phset_hs3)), 100, _hash_function, fun_less_int);

    printf("hs1 =");
    for(it_hs = hash_set_begin(phset_hs1);
        !iterator_equal(it_hs, hash_set_end(phset_hs1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs2 =");
    for(it_hs = hash_set_begin(phset_hs2);
        !iterator_equal(it_hs, hash_set_end(phset_hs2));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs3 =");
    for(it_hs = hash_set_begin(phset_hs3);
        !iterator_equal(it_hs, hash_set_end(phset_hs3));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs4 =");
    for(it_hs = hash_set_begin(phset_hs4);
        !iterator_equal(it_hs, hash_set_end(phset_hs4));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    printf("hs5 =");
    for(it_hs = hash_set_begin(phset_hs5);
        !iterator_equal(it_hs, hash_set_end(phset_hs5));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_set_destroy(phset_hs0);
    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);
    hash_set_destroy(phset_hs3);
    hash_set_destroy(phset_hs4);
    hash_set_destroy(phset_hs5);

    return 0;
}
