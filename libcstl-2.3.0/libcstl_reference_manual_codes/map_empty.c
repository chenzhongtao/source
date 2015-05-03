/*
 * map_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    map_t* pmap_m2 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);

    if(pmap_m1 == NULL || pmap_m2 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    map_init(pmap_m1);
    map_init(pmap_m2);

    pair_make(ppair_p, 1, 1);
    map_insert(pmap_m1, ppair_p);

    if(map_empty(pmap_m1))
    {
        printf("The map m1 is empty.\n");
    }
    else
    {
        printf("The map m1 is not empty.\n");
    }

    if(map_empty(pmap_m2))
    {
        printf("The map m2 is empty.\n");
    }
    else
    {
        printf("The map m2 is not empty.\n");
    }

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);
    map_destroy(pmap_m2);

    return 0;
}
