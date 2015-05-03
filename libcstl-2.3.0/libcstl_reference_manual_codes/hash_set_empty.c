/*
 * hash_set_empty.c
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
    hash_set_init(phset_hs2);

    hash_set_insert(phset_hs1, 1);

    if(hash_set_empty(phset_hs1))
    {
        printf("The hash_set hs1 is empty.\n");
    }
    else
    {
        printf("The hash_set hs1 is not empty.\n");
    }

    if(hash_set_empty(phset_hs2))
    {
        printf("The hash_set hs2 is empty.\n");
    }
    else
    {
        printf("The hash_set hs2 is not empty.\n");
    }

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);

    return 0;
}
