/*
 * hash_multiset_end.c
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

    hash_multiset_insert(phms_hms1, 1);
    hash_multiset_insert(phms_hms1, 2);
    hash_multiset_insert(phms_hms1, 3);

    it_hs = hash_multiset_end(phms_hms1);
    it_hs = iterator_prev(it_hs);
    printf("The last element of hs1 is %d.\n", *(int*)iterator_get_pointer(it_hs));

    hash_multiset_erase_pos(phms_hms1, it_hs);

    it_hs = hash_multiset_end(phms_hms1);
    it_hs = iterator_prev(it_hs);
    printf("The last element of hs1 is now %d.\n", *(int*)iterator_get_pointer(it_hs));

    hash_multiset_destroy(phms_hms1);

    return 0;
}
