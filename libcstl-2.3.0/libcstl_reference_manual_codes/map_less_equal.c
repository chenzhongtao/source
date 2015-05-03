/*
 * map_less_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    map_t* pmap_m2 = create_map(int, int);
    map_t* pmap_m3 = create_map(int, int);
    map_t* pmap_m4 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);
    int i = 0;

    if(pmap_m1 == NULL || pmap_m2 == NULL || pmap_m3 == NULL || pmap_m4 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    map_init(pmap_m1);
    map_init(pmap_m2);
    map_init(pmap_m3);
    map_init(pmap_m4);
    pair_init(ppair_p);

    for(i = 0; i < 3; ++i)
    {
        pair_make(ppair_p, i, i);
        map_insert(pmap_m1, ppair_p);
        map_insert(pmap_m4, ppair_p);
        pair_make(ppair_p, i, i * i);
        map_insert(pmap_m2, ppair_p);
        pair_make(ppair_p, i, i - 1);
        map_insert(pmap_m3, ppair_p);
    }

    if(map_less_equal(pmap_m1, pmap_m2))
    {
        printf("The map m1 is less than or equal to the map m2.\n");
    }
    else
    {
        printf("The map m1 is greater than the map m2.\n");
    }

    if(map_less_equal(pmap_m1, pmap_m3))
    {
        printf("The map m1 is less than or equal to the map m3.\n");
    }
    else
    {
        printf("The map m1 is greater than the map m3.\n");
    }

    if(map_less_equal(pmap_m1, pmap_m4))
    {
        printf("The map m1 is less than or equal to the map m4.\n");
    }
    else
    {
        printf("The map m1 is greater than the map m4.\n");
    }

    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    map_destroy(pmap_m3);
    map_destroy(pmap_m4);
    pair_destroy(ppair_p);

    return 0;
}
