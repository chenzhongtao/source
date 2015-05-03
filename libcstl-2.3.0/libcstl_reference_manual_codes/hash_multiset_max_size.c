/*
 * hash_multiset_max_size.c
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

    printf("The maximum possible length of the hash_multiset hs1 is: %d.\n",
        hash_multiset_max_size(phms_hms1));

    hash_multiset_destroy(phms_hms1);

    return 0;
}
