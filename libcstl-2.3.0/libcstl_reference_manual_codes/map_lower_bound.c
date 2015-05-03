/*
 * map_lower_bound.c
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

    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    it_m = map_lower_bound(pmap_m1, 2);
    printf("The first element of map m1 with a key of 2 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    /* If no match is found for this key, end() is returned */
    it_m = map_lower_bound(pmap_m1, 4);
    if(iterator_equal(it_m, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key of 4.\n");
    }
    else
    {
        printf("The element of map m1 with key of 4 is: %d.\n",
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }

    /*
     * The element at a specific location in the map can be found
     * using a dereferenced iterator addressing the location.
     */
    it_m = map_end(pmap_m1);
    it_m = iterator_prev(it_m);
    it_m = map_lower_bound(pmap_m1, *(int*)pair_first(iterator_get_pointer(it_m)));
    printf("The element of m1 with a key matching that of the last element is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);

    return 0;
}
