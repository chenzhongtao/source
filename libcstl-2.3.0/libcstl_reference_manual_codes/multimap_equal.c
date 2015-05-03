/*
 * multimap_equal.c
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
    int i = 0;

    if(pmmap_m1 == NULL || pmmap_m2 == NULL || pmmap_m3 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    multimap_init(pmmap_m1);
    multimap_init(pmmap_m2);
    multimap_init(pmmap_m3);
    pair_init(ppair_p);

    for(i = 0; i < 3; ++i)
    {
        pair_make(ppair_p, i, i);
        multimap_insert(pmmap_m1, ppair_p);
        multimap_insert(pmmap_m3, ppair_p);
        pair_make(ppair_p, i, i * i);
        multimap_insert(pmmap_m2, ppair_p);
    }

    if(multimap_equal(pmmap_m1, pmmap_m2))
    {
        printf("The multimaps m1 and m2 are equal.\n");
    }
    else
    {
        printf("The multimaps m1 and m2 are not equal.\n");
    }

    if(multimap_equal(pmmap_m1, pmmap_m3))
    {
        printf("The multimaps m1 and m3 are equal.\n");
    }
    else
    {
        printf("The multimaps m1 and m3 are not equal.\n");
    }

    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);
    multimap_destroy(pmmap_m3);
    pair_destroy(ppair_p);

    return 0;
}
