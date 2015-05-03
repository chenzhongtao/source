/*
 * map_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);
    map_iterator_t it_m;
    range_t r_r;

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

    r_r = map_equal_range(pmap_m1, 2);

    printf("The lower bound of the element with a key of 2 in the map m1 is: %d.\n", *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));
    printf("The upper bound of the element with a key of 2 in the map m1 is: %d.\n", *(int*)pair_second(iterator_get_pointer(r_r.it_end)));

    it_m = map_upper_bound(pmap_m1, 2);
    printf("A direct call of upper_bound(2) gives %d, matching the second element of the range returned by equal_range(2).\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    r_r = map_equal_range(pmap_m1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, map_end(pmap_m1)) && iterator_equal(r_r.it_end, map_end(pmap_m1)))
    {
        printf("The map m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of map m1 with a key >= 40 is %d.\n", *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);

    return 0;
}
