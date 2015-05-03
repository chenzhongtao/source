/*
 * hash_multiset_count.c
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
    hash_multiset_insert(phms_hms1, 1);

    /* Keys must be unique in hash_multiset, so duplicates are ignored */
    printf("The number of elements in hs1 with a sort key of 1 is: %d.\n",
        hash_multiset_count(phms_hms1, 1));

    printf("The number of elements in hs1 with a sort key of 2 is: %d.\n",
        hash_multiset_count(phms_hms1, 2));

    hash_multiset_destroy(phms_hms1);

    return 0;
}
