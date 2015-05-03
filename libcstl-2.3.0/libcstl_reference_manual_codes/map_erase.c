/*
 * map_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    map_t* pmap_m2 = create_map(int, int);
    map_t* pmap_m3 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);
    map_iterator_t it_m;
    int i = 0;
    size_t t_count = 0;

    if(pmap_m1 == NULL || pmap_m2 == NULL || pmap_m3 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    map_init(pmap_m1);
    map_init(pmap_m2);
    map_init(pmap_m3);

    for(i = 1; i < 5; ++i)
    {
        pair_make(ppair_p, i, i);
        map_insert(pmap_m1, ppair_p);
        pair_make(ppair_p, i, i * i);
        map_insert(pmap_m2, ppair_p);
        pair_make(ppair_p, i, i - 1);
        map_insert(pmap_m3, ppair_p);
    }

    /* The first function removes an element at a given position */
    it_m = map_begin(pmap_m1);
    it_m = iterator_next(it_m);
    map_erase_pos(pmap_m1, it_m);

    printf("After the second element is deleted, the map m1 is:");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    /* The second function remvoes elements in the range [first, last) */
    map_erase_range(pmap_m2, iterator_next(map_begin(pmap_m2)), iterator_prev(map_end(pmap_m2)));

    printf("After the middle two elements are deleted, the map m2 is:");
    for(it_m = map_begin(pmap_m2); !iterator_equal(it_m, map_end(pmap_m2)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    /* The third function removes elements with a given key */
    t_count = map_erase(pmap_m3, 2);

    printf("After the element with a key of 2 is deleted, the map m3 is:");
    for(it_m = map_begin(pmap_m3); !iterator_equal(it_m, map_end(pmap_m3)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");
    /* The third function returns the number of elements remvoed */
    printf("The number of elements removed from m3 is: %d.\n", t_count);

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    map_destroy(pmap_m3);

    return 0;
}
