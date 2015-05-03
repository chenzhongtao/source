/*
 * hash_set_count.c
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
    hash_set_insert(phset_hs1, 1);

    /* Keys must be unique in hash_set, so duplicates are ignored */
    printf("The number of elements in hs1 with a sort key of 1 is: %d.\n",
        hash_set_count(phset_hs1, 1));

    printf("The number of elements in hs1 with a sort key of 2 is: %d.\n",
        hash_set_count(phset_hs1, 2));

    hash_set_destroy(phset_hs1);

    return 0;
}
