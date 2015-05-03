/*
 * hash_multiset_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    range_t r_r;

    if(phms_hms1 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);

    hash_multiset_insert(phms_hms1, 10);
    hash_multiset_insert(phms_hms1, 20);
    hash_multiset_insert(phms_hms1, 30);

    r_r = hash_multiset_equal_range(phms_hms1, 20);
    printf("The upper bound of the element with a key of 20 in the hash_multiset hs1 is: %d.\n",
        *(int*)iterator_get_pointer(r_r.it_end));
    printf("The lower bound of the element with a key of 20 in the hash_multiset hs1 is: %d.\n",
        *(int*)iterator_get_pointer(r_r.it_begin));

    /* If no match is bound for the key, bouth element of the range returned end(). */
    r_r = hash_multiset_equal_range(phms_hms1, 40);
    if(iterator_equal(r_r.it_begin, hash_multiset_end(phms_hms1)) &&
       iterator_equal(r_r.it_end, hash_multiset_end(phms_hms1)))
    {
        printf("The hash_multiset hs1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_multiset hs1 with a key >= 40 is: %d.\n",
            *(int*)iterator_get_pointer(r_r.it_begin));
    }

    hash_multiset_destroy(phms_hms1);

    return 0;
}
