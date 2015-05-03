/*
 * multimap_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);
    multimap_iterator_t it_m;
    range_t r_r;

    if(pmmap_m1 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    multimap_init(pmmap_m1);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);

    r_r = multimap_equal_range(pmmap_m1, 2);

    printf("The lower bound of the element with a key of 2 in the multimap m1 is: %d.\n", *(int*)pair_second(iterator_get_pointer(r_r.it_begin)));
    printf("The upper bound of the element with a key of 2 in the multimap m1 is: %d.\n", *(int*)pair_second(iterator_get_pointer(r_r.it_end)));

    it_m = multimap_upper_bound(pmmap_m1, 2);
    printf("A direct call of upper_bound(2) gives %d, matching the second element of the range returned by equal_range(2).\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    r_r = multimap_equal_range(pmmap_m1, 4);
    /* If no match is found for the key, both elements of the range return end() */
    if(iterator_equal(r_r.it_begin, multimap_end(pmmap_m1)) && iterator_equal(r_r.it_end, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key less than 40.\n");
    }
    else
    {
        printf("The element of multimap m1 with a key >= 40 is %d.\n", *(int*)pair_first(iterator_get_pointer(r_r.it_begin)));
    }

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);

    return 0;
}
