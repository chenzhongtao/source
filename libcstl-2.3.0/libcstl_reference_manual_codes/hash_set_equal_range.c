/*
 * hash_set_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_set.h>

int main(int argc, char* argv[])
{
    hash_set_t* phset_hs1 = create_hash_set(int);
    range_t r_r;

    if(phset_hs1 == NULL)
    {
        return -1;
    }

    hash_set_init(phset_hs1);

    hash_set_insert(phset_hs1, 10);
    hash_set_insert(phset_hs1, 20);
    hash_set_insert(phset_hs1, 30);

    r_r = hash_set_equal_range(phset_hs1, 20);
    printf("The upper bound of the element with a key of 20 in the hash_set hs1 is: %d.\n",
        *(int*)iterator_get_pointer(r_r.it_end));
    printf("The lower bound of the element with a key of 20 in the hash_set hs1 is: %d.\n",
        *(int*)iterator_get_pointer(r_r.it_begin));

    /* If no match is bound for the key, bouth element of the range returned end(). */
    r_r = hash_set_equal_range(phset_hs1, 40);
    if(iterator_equal(r_r.it_begin, hash_set_end(phset_hs1)) &&
       iterator_equal(r_r.it_end, hash_set_end(phset_hs1)))
    {
        printf("The hash_set hs1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of hash_set hs1 with a key >= 40 is: %d.\n",
            *(int*)iterator_get_pointer(r_r.it_begin));
    }

    hash_set_destroy(phset_hs1);

    return 0;
}
