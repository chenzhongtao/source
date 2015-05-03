/*
 * hash_multiset_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_multiset_t* phms_hms1 = create_hash_multiset(int);
    hash_multiset_t* phms_hms2 = create_hash_multiset(int);
    hash_multiset_t* phms_hms3 = create_hash_multiset(int);
    int i = 0;

    if(phms_hms1 == NULL || phms_hms2 == NULL || phms_hms3 == NULL)
    {
        return -1;
    }

    hash_multiset_init(phms_hms1);
    hash_multiset_init(phms_hms2);
    hash_multiset_init(phms_hms3);

    for(i = 0; i < 3; ++i)
    {
        hash_multiset_insert(phms_hms1, i);
        hash_multiset_insert(phms_hms2, i * i);
        hash_multiset_insert(phms_hms3, i);
    }

    if(hash_multiset_equal(phms_hms1, phms_hms2))
    {
        printf("The hash_multisets hs1 and hs2 are equal.\n");
    }
    else
    {
        printf("The hash_multisets hs1 and hs2 are not equal.\n");
    }

    if(hash_multiset_equal(phms_hms1, phms_hms3))
    {
        printf("The hash_multisets hs1 and hs3 are equal.\n");
    }
    else
    {
        printf("The hash_multisets hs1 and hs3 are not equal.\n");
    }

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);
    hash_multiset_destroy(phms_hms3);

    return 0;
}
