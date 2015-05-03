/*
 * multimap_begin.c
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

    multimap_init(pmmap_m1);
    pair_init(ppair_p);

    pair_make(ppair_p, 0, 0);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 1, 1);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 4);
    multimap_insert(pmmap_m1, ppair_p);

    printf("The first element of m1 is %d\n", *(int*)pair_first(iterator_get_pointer(multimap_begin(pmmap_m1))));

    multimap_erase_pos(pmmap_m1, multimap_begin(pmmap_m1));

    printf("The first element of m1 is now %d\n", *(int*)pair_first(iterator_get_pointer(multimap_begin(pmmap_m1))));

    multimap_destroy(pmmap_m1);
    pair_destroy(ppair_p);

    return 0;
}
