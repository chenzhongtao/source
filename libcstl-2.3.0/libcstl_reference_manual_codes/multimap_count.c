/*
 * multimap_count.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);

    if(pmmap_m1 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    multimap_init(pmmap_m1);

    pair_make(ppair_p, 1, 1);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 1, 4);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 1);
    multimap_insert(pmmap_m1, ppair_p);

    /* Keys must be unique in multimap, so duplicates are ignored */
    printf("The number of elements in m1 with a sort key of 1 is: %d.\n", multimap_count(pmmap_m1, 1));
    printf("The number of elements in m1 with a sort key of 2 is: %d.\n", multimap_count(pmmap_m1, 2));
    printf("The number of elements in m1 with a sort key of 3 is: %d.\n", multimap_count(pmmap_m1, 3));

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);

    return 0;
}
