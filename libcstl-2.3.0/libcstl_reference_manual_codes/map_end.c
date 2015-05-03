/*
 * map_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m1 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);
    map_iterator_t it_m;

    if(pmap_m1 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    map_init(pmap_m1);

    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);

    it_m = map_end(pmap_m1);
    it_m = iterator_prev(it_m);
    printf("the value of the last element of m1 is: %d\n", *(int*)pair_second(iterator_get_pointer(it_m)));

    map_erase_pos(pmap_m1, it_m);

    it_m = map_end(pmap_m1);
    it_m = iterator_prev(it_m);
    printf("the value of the last element of m1 is now: %d\n", *(int*)pair_second(iterator_get_pointer(it_m)));

    pair_destroy(ppair_p);
    map_destroy(pmap_m1);

    return 0;
}
