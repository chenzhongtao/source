/*
 * hash_set_assign.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_t* phset_hs2 = create_hash_set(int);
    hash_set_iterator_t it_hs;

    if(phset_hs1 == NULL || phset_hs2 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);
    hash_set_init(phset_hs2);

    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);
    hash_set_insert(phset_hs2, 40);
    hash_set_insert(phset_hs2, 50);
    hash_set_insert(phset_hs2, 60);

    printf("hs1 =");
    for(it_hs = hash_set_begin(phset_hs1); !iterator_equal(it_hs, hash_set_end(phset_hs1)); it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_set_assign(phset_hs1, phset_hs2);
    printf("hs1 =");
    for(it_hs = hash_set_begin(phset_hs1); !iterator_equal(it_hs, hash_set_end(phset_hs1)); it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);

    return 0;
}
