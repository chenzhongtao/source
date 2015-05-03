/*
 * hash_set_less.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_t* phset_hs2 = create_hash_set(int);
    hash_set_t* phset_hs3 = create_hash_set(int);
    int i = 0;

    if(phset_hs1 == NULL || phset_hs2 == NULL || phset_hs3 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);
    hash_set_init(phset_hs2);
    hash_set_init(phset_hs3);

    for(i = 0; i < 3; ++i)
    {
        hash_set_insert(phset_hs1, i);
        hash_set_insert(phset_hs2, i * i);
        hash_set_insert(phset_hs3, i - 1);
    }

    if(hash_set_less(phset_hs1, phset_hs2))
    {
        printf("The hash_set hs1 is less than the hash_set hs2.\n");
    }
    else
    {
        printf("The hash_set hs1 is not less than the hash_set hs2.\n");
    }

    if(hash_set_less(phset_hs1, phset_hs3))
    {
        printf("The hash_set hs1 is less than the hash_set hs3.\n");
    }
    else
    {
        printf("The hash_set hs1 is not less than the hash_set hs3.\n");
    }

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);
    hash_set_destroy(phset_hs3);

    return 0;
}
