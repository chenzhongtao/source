/*
 * hash_set_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_iterator_t it_hs;

    if(phset_hs1 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);

    hash_set_insert(phset_hs1, 1);
    hash_set_insert(phset_hs1, 2);
    hash_set_insert(phset_hs1, 3);

    it_hs = hash_set_end(phset_hs1);
    it_hs = iterator_prev(it_hs);
    printf("The last element of hs1 is %d.\n", *(int*)iterator_get_pointer(it_hs));

    hash_set_erase_pos(phset_hs1, it_hs);

    it_hs = hash_set_end(phset_hs1);
    it_hs = iterator_prev(it_hs);
    printf("The last element of hs1 is now %d.\n", *(int*)iterator_get_pointer(it_hs));

    hash_set_destroy(phset_hs1);

    return 0;
}
