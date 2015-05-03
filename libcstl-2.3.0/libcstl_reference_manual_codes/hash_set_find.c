/*
 * hash_set_find.c
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

    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);

    it_hs = hash_set_find(phset_hs1, 20);
    printf("The element of hash_set hs1 with a key of 20 is: %d.\n",
        *(int*)iterator_get_pointer(it_hs));

    it_hs = hash_set_find(phset_hs1, 40);

    /* If no match is found for the key, end() is returned */
    if(iterator_equal(it_hs, hash_set_end(phset_hs1)))
    {
        printf("The hash_set hs1 doesn't have an element with a key of 40.\n");
    }
    else
    {
        printf("The element of hash_set hs1 with a key of 40 is: %d.\n",
            *(int*)iterator_get_pointer(it_hs));
    }

    /*
     * The element at a specific location in the hash_set can be found
     * by using a dereferenced iterator addressing the location.
     */
    it_hs = iterator_prev(hash_set_end(phset_hs1));
    it_hs = hash_set_find(phset_hs1, *(int*)iterator_get_pointer(it_hs));
    printf("The element of hs1 with a key matching that of the last element is: %d.\n",
        *(int*)iterator_get_pointer(it_hs));

    hash_set_destroy(phset_hs1);

    return 0;
}
