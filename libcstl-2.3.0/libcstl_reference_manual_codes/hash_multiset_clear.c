/*
 * hash_multiset_clear.c
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

    printf("The size of the hash_multiset is initially %d.\n", hash_multiset_size(phms_hms1));

    hash_multiset_clear(phms_hms1);

    printf("The size of the hash_multiset after clearing is %d.\n", hash_multiset_size(phms_hms1));

    hash_multiset_destroy(phms_hms1);

    return 0;
}
