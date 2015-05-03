/*
 * map_count.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);

    if(pmap_m1 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    map_init(pmap_m1);

    pair_make(ppair_p, 1, 1);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 1, 4);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    map_insert(pmap_m1, ppair_p);

    /* Keys must be unique in map, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n", map_count(pmap_m1, 1));
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n", map_count(pmap_m1, 2));
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n", map_count(pmap_m1, 3));

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);

    return 0;
}
