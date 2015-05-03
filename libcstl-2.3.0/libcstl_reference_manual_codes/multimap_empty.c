/*
 * multimap_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    multimap_t* pmmap_m2 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);

    if(pmmap_m1 == NULL || pmmap_m2 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    multimap_init(pmmap_m1);
    multimap_init(pmmap_m2);

    pair_make(ppair_p, 1, 1);
    multimap_insert(pmmap_m1, ppair_p);

    if(multimap_empty(pmmap_m1))
    {
        printf("The multimap m1 is empty.\n");
    }
    else
    {
        printf("The multimap m1 is not empty.\n");
    }

    if(multimap_empty(pmmap_m2))
    {
        printf("The multimap m2 is empty.\n");
    }
    else
    {
        printf("The multimap m2 is not empty.\n");
    }

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);

    return 0;
}
