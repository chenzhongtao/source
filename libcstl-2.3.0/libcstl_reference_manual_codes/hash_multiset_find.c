/*
 * hash_multiset_find.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_iterator_t it_hs;

    if(phms_hms1 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);

    hash_multiset_insert(phms_hms1, 10);
    hash_multiset_insert(phms_hms1, 20);
    hash_multiset_insert(phms_hms1, 30);

    it_hs = hash_multiset_find(phms_hms1, 20);
    printf("The element of hash_multiset hs1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_hs));

    it_hs = hash_multiset_find(phms_hms1, 40);

    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_hs, hash_multiset_end(phms_hms1)))
    {
        printf("The hash_multiset hs1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of hash_multiset hs1 with a key of 40 is: %d.\n",
            *(int*)iterator_get_pointer(it_hs));
    }

    /*
     * The element at a specific location in the hash_multiset can be found
     * by using a dereferenced iterator addressing the location.
     */
    it_hs = iterator_prev(hash_multiset_end(phms_hms1));
    it_hs = hash_multiset_find(phms_hms1, *(int*)iterator_get_pointer(it_hs));
    printf("The element of hs1 with a key matching that of the last element is: %d.\n",
        *(int*)iterator_get_pointer(it_hs));

    hash_multiset_destroy(phms_hms1);

    return 0;
}
