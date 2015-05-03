/*
 * hash_multiset_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_t* phms_hms2 = create_hash_multiset(int);
    hash_multiset_t* phms_hms3 = create_hash_multiset(int);
    hash_multiset_iterator_t it_hs;
    size_t t_count = 0;
    int i = 0;

    if(phms_hms1 == NULL || phms_hms2 == NULL || phms_hms3 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);
    hash_multiset_init(phms_hms2);
    hash_multiset_init(phms_hms3);

    for(i = 1; i < 5; ++i)
    {
        hash_multiset_insert(phms_hms1, i);
        hash_multiset_insert(phms_hms2, i * i);
        hash_multiset_insert(phms_hms3, i - 1);
    }

    /* The first function removes an element at a given position */
    it_hs = iterator_next(hash_multiset_begin(phms_hms1));
    hash_multiset_erase_pos(phms_hms1, it_hs);

    printf("After the second element is deleted, the hash_multiset hs1 is: ");
    for(it_hs = hash_multiset_begin(phms_hms1);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    /* The second function removes elements in the range [first, last) */
    hash_multiset_erase_range(phms_hms2, iterator_next(hash_multiset_begin(phms_hms2)),
        iterator_prev(hash_multiset_end(phms_hms2)));

    printf("After the middle two elements are deleted, the hash_multiset hs2 is: ");
    for(it_hs = hash_multiset_begin(phms_hms2);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms2));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    /* The third function removes elements with a given key */
    t_count = hash_multiset_erase(phms_hms3, 2);

    printf("After the element with a key of 2 is deleted, the hash_multiset hs3 is: ");
    for(it_hs = hash_multiset_begin(phms_hms3);
        !iterator_equal(it_hs, hash_multiset_end(phms_hms3));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);
    hash_multiset_destroy(phms_hms3);

    return 0;
}
