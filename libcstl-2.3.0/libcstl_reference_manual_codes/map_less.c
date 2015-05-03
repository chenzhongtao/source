/*
 * map_less.c
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
        pair_make(ppair_p, i, i * i);
        map_insert(pmap_m2, ppair_p);
        pair_make(ppair_p, i, i - 1);
        map_insert(pmap_m3, ppair_p);
    }

    if(map_less(pmap_m1, pmap_m2))
    {
        printf("The map m1 is less than the map m2.\n");
    }
    else
    {
        printf("The map m1 is not less than the map m2.\n");
    }

    if(map_less(pmap_m1, pmap_m3))
    {
        printf("The map m1 is less than the map m3.\n");
    }
    else
    {
        printf("The map m1 is not less than the map m3.\n");
    }

    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    map_destroy(pmap_m3);
    pair_destroy(ppair_p);

    return 0;
}
