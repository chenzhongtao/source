/*
 * multimap_find.c
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
    pair_make(ppair_p, 3, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);

    it_m = multimap_find(pmmap_m1, 2);
    printf("The element of multimap m1 with a key of 2 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    it_m = multimap_find(pmmap_m1, 3);
    printf("The first element of multimap m1 with a key of 3 is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    /* If no match is found for the key, end() is returned */
    it_m = multimap_find(pmmap_m1, 4);
    if(iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The multimap m1 doesn't have an element with a key of 4.\n");
    }
    else
    {
        printf("The element of multimap m1 with a key of 4 is: %d.\n",
            *(int*)pair_second(iterator_get_pointer(it_m)));
    }

    /*
     * The element at a specific location in the multimap can be found
     * using a dereferenced iterator addressing the location
     */
    it_m = multimap_end(pmmap_m1);
    it_m = iterator_prev(it_m);
    it_m = multimap_find(pmmap_m1, *(int*)pair_first(iterator_get_pointer(it_m)));
    printf("The element of m1 with a key matching that of the last element is: %d.\n",
        *(int*)pair_second(iterator_get_pointer(it_m)));

    /*
     * Note that the first element with a key equal to
     * the key of the last element is not the last element.
     */
    if(iterator_equal(it_m, iterator_prev(multimap_end(pmmap_m1))))
    {
        printf("This is the last element of multimap m1.\n");
    }
    else
    {
        printf("This is not the last element of multimap m1.\n");
    }

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);

    return 0;
}
