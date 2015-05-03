/*
 * map_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    map_t* pmap_m0 = create_map(int, int);
    map_t* pmap_m1 = create_map(int, int);
    map_t* pmap_m2 = create_map(int, int);
    map_t* pmap_m3 = create_map(int, int);
    map_t* pmap_m4 = create_map(int, int);
    map_t* pmap_m5 = create_map(int, int);
    pair_t* ppair_p = create_pair(int, int);
    map_iterator_t it_m;

    if(pmap_m0 == NULL || pmap_m1 == NULL || pmap_m2 == NULL || pmap_m3 == NULL || pmap_m4 == NULL || pmap_m5 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);

    /* Create an empty map m0 of key type integer */
    map_init(pmap_m0);

    /* 
     * Create an empty map m1 with the key comparison
     * function of less than, then insert 4 elements.
     */
    map_init_ex(pmap_m1, fun_less_int);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    map_insert(pmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    map_insert(pmap_m1, ppair_p);

    /*
     * Create an empty map m2 with the key comparison
     * function of greater than, then insert 2 elements.
     */
    map_init_ex(pmap_m2, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    map_insert(pmap_m2, ppair_p);
    pair_make(ppair_p, 2, 20);
    map_insert(pmap_m2, ppair_p);

    /* Create a copy, map m3, of map m1 */
    map_init_copy(pmap_m3, pmap_m1);

    /* Create a map m4 by copying the range m1[first, last) */
    map_init_copy_range(pmap_m4, map_begin(pmap_m1), iterator_advance(map_begin(pmap_m1), 2));

    /* 
     * Create a map m5 by copying the range m3[first, last)
     * and with the key comparison function less than.
     */
    map_init_copy_range_ex(pmap_m5, map_begin(pmap_m3), iterator_next(map_begin(pmap_m3)), fun_less_int);

    printf("m1 =");
    for(it_m = map_begin(pmap_m1); !iterator_equal(it_m, map_end(pmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m2 =");
    for(it_m = map_begin(pmap_m2); !iterator_equal(it_m, map_end(pmap_m2)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m3 =");
    for(it_m = map_begin(pmap_m3); !iterator_equal(it_m, map_end(pmap_m3)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m4 =");
    for(it_m = map_begin(pmap_m4); !iterator_equal(it_m, map_end(pmap_m4)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m5 =");
    for(it_m = map_begin(pmap_m5); !iterator_equal(it_m, map_end(pmap_m5)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    map_destroy(pmap_m0);
    map_destroy(pmap_m1);
    map_destroy(pmap_m2);
    map_destroy(pmap_m3);
    map_destroy(pmap_m4);
    map_destroy(pmap_m5);
    pair_destroy(ppair_p);

    return 0;
}
