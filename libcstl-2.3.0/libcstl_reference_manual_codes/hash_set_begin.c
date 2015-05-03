/*
 * hash_set_begin.c
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
    hash_set_insert(phset_hs1, 2);
    hash_set_insert(phset_hs1, 3);

    printf("The first element of hs1 is %d.\n",
        *(int*)iterator_get_pointer(hash_set_begin(phset_hs1)));

    hash_set_erase_pos(phset_hs1, hash_set_begin(phset_hs1));

    printf("The first element of hs1 is now %d.\n",
        *(int*)iterator_get_pointer(hash_set_begin(phset_hs1)));

    hash_set_destroy(phset_hs1);

    return 0;
}
