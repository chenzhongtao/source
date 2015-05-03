/*
 * hash_set_bucket_count.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_t* phset_hs2 = create_hash_set(int);

    if(phset_hs1 == NULL || phset_hs2 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);
    hash_set_init_ex(phset_hs2, 100, NULL, NULL);

    printf("The default bucket count of hs1 is %d.\n", hash_set_bucket_count(phset_hs1));
    printf("The custom bucket count of hs2 is %d.\n", hash_set_bucket_count(phset_hs2));

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);

    return 0;
}
