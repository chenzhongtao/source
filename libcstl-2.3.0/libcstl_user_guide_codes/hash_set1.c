/*
 * hash_set1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_coll = create_hash_set(int);
    hash_set_iterator_t it_pos;
    int i = 0;

    if(phset_coll == NULL)
    {
        return -1;
    }

    hash_set_init(phset_coll);

    hash_set_insert(phset_coll, 7);
    hash_set_insert(phset_coll, 99);
    hash_set_insert(phset_coll, 63);
    hash_set_insert(phset_coll, 2);
    hash_set_insert(phset_coll, 108);
    hash_set_insert(phset_coll, 444);
    hash_set_insert(phset_coll, 53);
    hash_set_insert(phset_coll, 55);
    hash_set_insert(phset_coll, 255);
    hash_set_insert(phset_coll, 55);

    printf("bucket count : %u\n", hash_set_bucket_count(phset_coll));
    for(it_pos = hash_set_begin(phset_coll);
        !iterator_equal(it_pos, hash_set_end(phset_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    for(i = 0; i < 50; ++i)
    {
        hash_set_insert(phset_coll, i);
    }

    printf("bucket count : %u\n", hash_set_bucket_count(phset_coll));
    for(it_pos = hash_set_begin(phset_coll);
        !iterator_equal(it_pos, hash_set_end(phset_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    hash_set_destroy(phset_coll);

    return 0;
}
