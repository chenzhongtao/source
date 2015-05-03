/*
 * map_clear.c
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
    pair_make(ppair_p, 2, 4);
    map_insert(pmap_m1, ppair_p);

    printf("The size of the map is initially %d.\n", map_size(pmap_m1));

    map_clear(pmap_m1);
    printf("The size of the map after clearing is %d.\n", map_size(pmap_m1));

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);

    return 0;
}
