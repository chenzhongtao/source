/*
 * multimap_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    multimap_t* pmmap_m2 = create_multimap(int, int);
    multimap_t* pmmap_m3 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);
    multimap_iterator_t it_m;
    int i = 0;
    size_t t_count = 0;

    if(pmmap_m1 == NULL || pmmap_m2 == NULL || pmmap_m3 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    multimap_init(pmmap_m1);
    multimap_init(pmmap_m2);
    multimap_init(pmmap_m3);

    for(i = 1; i < 5; ++i)
    {
        pair_make(ppair_p, i, i);
        multimap_insert(pmmap_m1, ppair_p);
        pair_make(ppair_p, i, i * i);
        multimap_insert(pmmap_m2, ppair_p);
        pair_make(ppair_p, i, i - 1);
        multimap_insert(pmmap_m3, ppair_p);
    }

    /* The first function removes an element at a given position */
    it_m = multimap_begin(pmmap_m1);
    it_m = iterator_next(it_m);
    multimap_erase_pos(pmmap_m1, it_m);

    printf("After the second element is deleted, the multimap m1 is:");
    for(it_m = multimap_begin(pmmap_m1); !iterator_equal(it_m, multimap_end(pmmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    /* The second function remvoes elements in the range [first, last) */
    multimap_erase_range(pmmap_m2, iterator_next(multimap_begin(pmmap_m2)), iterator_prev(multimap_end(pmmap_m2)));

    printf("After the middle two elements are deleted, the multimap m2 is:");
    for(it_m = multimap_begin(pmmap_m2); !iterator_equal(it_m, multimap_end(pmmap_m2)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    /* The third function removes elements with a given key */
    pair_make(ppair_p, 2, 5);
    multimap_insert(pmmap_m3, ppair_p);
    t_count = multimap_erase(pmmap_m3, 2);

    printf("After the element with a key of 2 is deleted, the multimap m3 is:");
    for(it_m = multimap_begin(pmmap_m3); !iterator_equal(it_m, multimap_end(pmmap_m3)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");
    /* The third function returns the number of elements remvoed */
    printf("The number of elements removed from m3 is: %d.\n", t_count);

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);
    multimap_destroy(pmmap_m3);

    return 0;
}
