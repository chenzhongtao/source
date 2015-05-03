/*
 * hash_multiset_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_t* phms_hms2 = create_hash_multiset(int);

    if(phms_hms1 == NULL || phms_hms2 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);
    hash_multiset_init(phms_hms2);

    hash_multiset_insert(phms_hms1, 1);

    if(hash_multiset_empty(phms_hms1))
    {
        printf("The hash_multiset hs1 is empty.\n");
    }
    else
    {
        printf("The hash_multiset hs1 is not empty.\n");
    }

    if(hash_multiset_empty(phms_hms2))
    {
        printf("The hash_multiset hs2 is empty.\n");
    }
    else
    {
        printf("The hash_multiset hs2 is not empty.\n");
    }

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);

    return 0;
}
