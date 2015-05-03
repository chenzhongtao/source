/*
 * map_swap.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    map_t* pmap_m2 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);
    map_iterator_t it_m;

    if(pmap_m1 == NULL || pmap_m2 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    map_init(pmap_m1);
    map_init(pmap_m2);

    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    pair_make(ppair_p, 10, 100);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 20, 200);
    map_insert(pmap_m2, ppair_p);

    printf("The original map m1 is:");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    map_swap(pmap_m1, pmap_m2);

    printf("After swapping with m2, map m1 is:");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);
    map_destroy(pmap_m2);

    return 0;
}
