/*
 * hash_set_max_size.c
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

    printf("The maximum possible length of the hash_set hs1 is: %d.\n",
        hash_set_max_size(phset_hs1));

    hash_set_destroy(phset_hs1);

    return 0;
}
