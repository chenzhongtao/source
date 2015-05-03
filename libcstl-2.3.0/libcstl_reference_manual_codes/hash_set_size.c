/*
 * hash_set_size.c
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

    hash_set_insert(phset_hs1, 1);
    printf("The hash_set hs1 length is %d.\n", hash_set_size(phset_hs1));

    hash_set_insert(phset_hs1, 2);
    printf("The hash_set hs1 length is now %d.\n", hash_set_size(phset_hs1));

    hash_set_destroy(phset_hs1);

    return 0;
}
