/*
 * multimap_upper_bound.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);
    multimap_iterator_t it_m;

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
    pair_make(ppair_p, 3, 40);
    multimap_insert(pmmap_m1, ppair_p);

    it_m = multimap_upper_bound(pmmap_m1, 1);
    printf("The first element of multimap m1 with a key greater than 1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    it_m = multimap_upper_bound(pmmap_m1, 2);
    printf("The first element of multimap m1 with a key greater than 2 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    /* If no match is found for the key, end is returned */
    it_m = multimap_upper_bound(pmmap_m1, 4);
    if(iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key greater than 4.\n");
    }
    else
    {
        printf("The element of multimap m1 with a key > 4 is: %d.\n",
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }

    /*
     * The element at a specific location in the multimap can be found
     * using a dereferenced iterator addressing the location
     */
    it_m = multimap_begin(pmmap_m1);
    it_m = multimap_upper_bound(pmmap_m1, *(int*)pair_first(iterator_get_pointer(it_m)));
    printf("The first element of m1 with a key greater than that of the initial element of m1 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);

    return 0;
}
