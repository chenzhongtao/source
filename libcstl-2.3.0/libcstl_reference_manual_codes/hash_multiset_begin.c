/*
 * hash_multiset_begin.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);

    if(phms_hms1 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);

    hash_multiset_insert(phms_hms1, 1);
    hash_multiset_insert(phms_hms1, 2);
    hash_multiset_insert(phms_hms1, 3);

    printf("The first element of hs1 is %d.\n",
        *(int*)iterator_get_pointer(hash_multiset_begin(phms_hms1)));

    hash_multiset_erase_pos(phms_hms1, hash_multiset_begin(phms_hms1));

    printf("The first element of hs1 is now %d.\n",
        *(int*)iterator_get_pointer(hash_multiset_begin(phms_hms1)));

    hash_multiset_destroy(phms_hms1);

    return 0;
}
