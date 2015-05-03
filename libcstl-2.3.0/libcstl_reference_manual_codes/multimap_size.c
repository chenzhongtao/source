/*
 * multimap_size.c
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
    printf("The multimap length is %d.\n", multimap_size(pmmap_m1));

    pair_make(ppair_p, 2, 4);
    multimap_insert(pmmap_m1, ppair_p);
    printf("The multimap length is now %d.\n", multimap_size(pmmap_m1));

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);

    return 0;
}
