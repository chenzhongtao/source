/*
 * hash_map_at.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/chash_map.h>

int main(int argc, char* argv[])
{
    hash_map_t* phm_hm1 = create_hash_map(int, int);
    pair_t* ppr_hm = create_pair(int, int);
    hash_map_iterator_t it_hm;

    if(phm_hm1 == NULL || ppr_hm == NULL)
    {
        return -1;
    }

    hash_map_init(phm_hm1);
    pair_init(ppr_hm);

    /*
     * Insert a data value of 10 with a key of 1
     * into a hash_map uing the at function
     */
    *(int*)hash_map_at(phm_hm1, 1) = 10;

    /*
     * Compare other ways to insert data into a hash_map
     */
    pair_make(ppr_hm, 2, 20);
    hash_map_insert(phm_hm1, ppr_hm);
    pair_make(ppr_hm, 3, 30);
    hash_map_insert(phm_hm1, ppr_hm);

    printf("The keys of the mapped elements are:");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" %d", *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("The values of the mapped elements are:");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" %d", *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    /*
     * If the key already exist, the at function
     * changes the value of the datum in the element
     */
    *(int*)hash_map_at(phm_hm1, 2) = 40;

    /*
     * The at function will also insert the value of the data
     * type's default if the value is unspecified
     */
    hash_map_at(phm_hm1, 5);

    printf("The keys of the mapped elements are:");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" %d", *(int*)pair_first((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    printf("The values of the mapped elements are:");
    for(it_hm = hash_map_begin(phm_hm1);
        !iterator_equal(it_hm, hash_map_end(phm_hm1));
        it_hm = iterator_next(it_hm))
    {
        printf(" %d", *(int*)pair_second((pair_t*)iterator_get_pointer(it_hm)));
    }
    printf("\n");

    hash_map_destroy(phm_hm1);
    pair_destroy(ppr_hm);

    return 0;
}
