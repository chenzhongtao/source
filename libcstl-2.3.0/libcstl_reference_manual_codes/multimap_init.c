/*
 * multimap_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m0 = create_multimap(int, int);
    multimap_t* pmmap_m1 = create_multimap(int, int);
    multimap_t* pmmap_m2 = create_multimap(int, int);
    multimap_t* pmmap_m3 = create_multimap(int, int);
    multimap_t* pmmap_m4 = create_multimap(int, int);
    multimap_t* pmmap_m5 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);
    multimap_iterator_t it_m;

    if(pmmap_m0 == NULL || pmmap_m1 == NULL || pmmap_m2 == NULL || pmmap_m3 == NULL || pmmap_m4 == NULL || pmmap_m5 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);

    /* Create an empty multimap m0 of key type integer */
    multimap_init(pmmap_m0);

    /* 
     * Create an empty multimap m1 with the key comparison
     * function of less than, then insert 4 elements.
     */
    multimap_init_ex(pmmap_m1, fun_less_int);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);

    /*
     * Create an empty multimap m2 with the key comparison
     * function of greater than, then insert 2 elements.
     */
    multimap_init_ex(pmmap_m2, fun_greater_int);
    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m2, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m2, ppair_p);

    /* Create a copy, multimap m3, of multimap m1 */
    multimap_init_copy(pmmap_m3, pmmap_m1);

    /* Create a multimap m4 by copying the range m1[first, last) */
    multimap_init_copy_range(pmmap_m4, multimap_begin(pmmap_m1), iterator_advance(multimap_begin(pmmap_m1), 2));

    /* 
     * Create a multimap m5 by copying the range m3[first, last)
     * and with the key comparison function less than.
     */
    multimap_init_copy_range_ex(pmmap_m5, multimap_begin(pmmap_m3), iterator_next(multimap_begin(pmmap_m3)), fun_less_int);

    printf("m1 =");
    for(it_m = multimap_begin(pmmap_m1); !iterator_equal(it_m, multimap_end(pmmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m2 =");
    for(it_m = multimap_begin(pmmap_m2); !iterator_equal(it_m, multimap_end(pmmap_m2)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m3 =");
    for(it_m = multimap_begin(pmmap_m3); !iterator_equal(it_m, multimap_end(pmmap_m3)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m4 =");
    for(it_m = multimap_begin(pmmap_m4); !iterator_equal(it_m, multimap_end(pmmap_m4)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    printf("m5 =");
    for(it_m = multimap_begin(pmmap_m5); !iterator_equal(it_m, multimap_end(pmmap_m5)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    multimap_destroy(pmmap_m0);
    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);
    multimap_destroy(pmmap_m3);
    multimap_destroy(pmmap_m4);
    multimap_destroy(pmmap_m5);
    pair_destroy(ppair_p);

    return 0;
}
