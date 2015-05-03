/*
 * hash_multiset_insert.c
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
    hash_multiset_insert(phms_hms1, 40);

    printf("The original hs1 =");
    for(it_hs = hash_multiset_begin(phms_hms1);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    it_hs = hash_multiset_insert(phms_hms1, 10);
    if(iterator_equal(it_hs, hash_multiset_end(phms_hms1)))
    {
        printf("The element 10 already exist in hs1.\n");
    }
    else
    {
        printf("The element 10 was inserted inhs1 successfully.\n");
    }

    hash_multiset_insert(phms_hms1, 80);
    printf("After the insertions, hs1 =");
    for(it_hs = hash_multiset_begin(phms_hms1);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_multiset_insert(phms_hms2, 100);
    hash_multiset_insert_range(phms_hms2, iterator_next(hash_multiset_begin(phms_hms1)),
        iterator_prev(hash_multiset_end(phms_hms1)));

    printf("hs2 =");
    for(it_hs = hash_multiset_begin(phms_hms2);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms2));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);

    return 0;
}
