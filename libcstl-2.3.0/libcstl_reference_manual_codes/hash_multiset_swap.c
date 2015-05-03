/*
 * hash_multiset_swap.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_t* phms_hms2 = create_hash_multiset(int);
    hash_multiset_iterator_t it_hs;

    if(phms_hms1 == NULL || phms_hms2 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);
    hash_multiset_init(phms_hms2);

    hash_multiset_insert(phms_hms1, 10);
    hash_multiset_insert(phms_hms1, 20);
    hash_multiset_insert(phms_hms1, 30);
    hash_multiset_insert(phms_hms2, 100);
    hash_multiset_insert(phms_hms2, 200);

    printf("The original hash_multiset hs1 is:");
    for(it_hs = hash_multiset_begin(phms_hms1);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_multiset_swap(phms_hms1, phms_hms2);

    printf("After swapping with hs2, hash_multiset hs1 is:");
    for(it_hs = hash_multiset_begin(phms_hms1);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);

    return 0;
}
