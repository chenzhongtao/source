/*
 * multimap_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);
    multimap_iterator_t it_m;

    if(pmmap_m1 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    multimap_init(pmmap_m1);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);

    it_m = multimap_end(pmmap_m1);
    it_m = iterator_prev(it_m);
    printf("the value of the last element of m1 is: %d\n", *(int*)pair_second(iterator_get_pointer(it_m)));

    multimap_erase_pos(pmmap_m1, it_m);

    it_m = multimap_end(pmmap_m1);
    it_m = iterator_prev(it_m);
    printf("the value of the last element of m1 is now: %d\n", *(int*)pair_second(iterator_get_pointer(it_m)));

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);

    return 0;
}
