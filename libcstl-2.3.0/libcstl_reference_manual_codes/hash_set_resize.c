/*
 * hash_set_resize.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);

    if(phset_hs1 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);

    printf("The bucket count of hash_set hs1 is: %d.\n",
        hash_set_bucket_count(phset_hs1));

    hash_set_resize(phset_hs1, 100);

    printf("The bucket count of hash_set hs1 is now: %d.\n",
        hash_set_bucket_count(phset_hs1));

    hash_set_destroy(phset_hs1);

    return 0;
}
