/*
 * hash_set_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    hash_set_t* phset_hs2 = create_hash_set(int);
    hash_set_t* phset_hs3 = create_hash_set(int);
    hash_set_iterator_t it_hs;
    size_t t_count = 0;
    int i = 0;

    if(phset_hs1 == NULL || phset_hs2 == NULL || phset_hs3 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);
    hash_set_init(phset_hs2);
    hash_set_init(phset_hs3);

    for(i = 1; i < 5; ++i)
    {
        hash_set_insert(phset_hs1, i);
        hash_set_insert(phset_hs2, i * i);
        hash_set_insert(phset_hs3, i - 1);
    }

    /* The first function removes an element at a given position */
    it_hs = iterator_next(hash_set_begin(phset_hs1));
    hash_set_erase_pos(phset_hs1, it_hs);

    printf("After the second element is deleted, the hash_set hs1 is: ");
    for(it_hs = hash_set_begin(phset_hs1);
        !iterator_equal(it_hs, hash_set_end(phset_hs1));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    /* The second function removes elements in the range [first, last) */
    hash_set_erase_range(phset_hs2, iterator_next(hash_set_begin(phset_hs2)),
        iterator_prev(hash_set_end(phset_hs2)));

    printf("After the middle two elements are deleted, the hash_set hs2 is: ");
    for(it_hs = hash_set_begin(phset_hs2);
        !iterator_equal(it_hs, hash_set_end(phset_hs2));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    /* The third function removes elements with a given key */
    t_count = hash_set_erase(phset_hs3, 2);

    printf("After the element with a key of 2 is deleted, the hash_set hs3 is: ");
    for(it_hs = hash_set_begin(phset_hs3);
        !iterator_equal(it_hs, hash_set_end(phset_hs3));
        it_hs = iterator_next(it_hs))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_hs));
    }
    printf("\n");

    hash_set_destroy(phset_hs1);
    hash_set_destroy(phset_hs2);
    hash_set_destroy(phset_hs3);

    return 0;
}
