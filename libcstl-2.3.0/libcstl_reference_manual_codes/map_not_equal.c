/*
 * map_not_equal.c
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
    int i = 0;

    if(pmap_m1 == NULL || pmap_m2 == NULL || pmap_m3 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    map_init(pmap_m1);
    map_init(pmap_m2);
    map_init(pmap_m3);
    pair_init(ppair_p);

    for(i = 0; i < 3; ++i)
    {
        pair_make(ppair_p, i, i);
        map_insert(pmap_m1, ppair_p);
        map_insert(pmap_m3, ppair_p);
        pair_make(ppair_p, i, i * i);
        map_insert(pmap_m2, ppair_p);
    }

    if(map_not_equal(pmap_m1, pmap_m2))
    {
        printf("The maps m1 and m2 are not equal.\n");
    }
    else
    {
        printf("The maps m1 and m2 are equal.\n");
    }

    if(map_not_equal(pmap_m1, pmap_m3))
    {
        printf("The maps m1 and m3 are not equal.\n");
    }
    else
    {
        printf("The maps m1 and m3 are equal.\n");
    }

    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    map_destroy(pmap_m3);
    pair_destroy(ppair_p);

    return 0;
}
