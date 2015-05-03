/*
 * hash_multiset_bucket_count.c
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
    hash_multiset_init_ex(phms_hms2, 100, NULL, NULL);

    printf("The default bucket count of hs1 is %d.\n", hash_multiset_bucket_count(phms_hms1));
    printf("The custom bucket count of hs2 is %d.\n", hash_multiset_bucket_count(phms_hms2));

    hash_multiset_destroy(phms_hms1);
    hash_multiset_destroy(phms_hms2);

    return 0;
}
