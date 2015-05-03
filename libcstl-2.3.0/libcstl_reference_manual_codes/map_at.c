/*
 * map_at.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);
    map_iterator_t it_m;

    if(pmap_m1 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    map_init(pmap_m1);

    /*
     * Insert a data value of 10 with a key of 1
     * into a map using the at() function.
     */
    *(int*)map_at(pmap_m1, 1) = 10;

    /* Insert datas into a map using insert() function. */
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    printf("The keys of the mapped elements are:");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_first(iterator_get_pointer(it_m)));
    }
    printf("\n");
    printf("The values of the mapped elements are:");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    /*
     * If the key alread exists, at() funtiont changes the value
     * of the datum in the element.
     */
    *(int*)map_at(pmap_m1, 2) = 40;

    /*
     * at() function will also insert the value of the data
     * type's default value if the value is unspecified.
     */
    map_at(pmap_m1, 5);

    printf("The keys of the mapped elements are now:");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_first(iterator_get_pointer(it_m)));
    }
    printf("\n");
    printf("The values of the mapped elements are now:");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);

    return 0;
}
