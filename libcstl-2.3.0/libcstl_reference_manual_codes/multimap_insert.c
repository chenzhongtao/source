/*
 * multimap_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    multimap_t* pmmap_m2 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);
    multimap_iterator_t it_m;

    if(pmmap_m1 == NULL || pmmap_m2 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    multimap_init(pmmap_m1);
    multimap_init(pmmap_m2);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 20);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 3, 30);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 4, 40);
    multimap_insert(pmmap_m1, ppair_p);

    printf("The original key values of m1 =");
    for(it_m = multimap_begin(pmmap_m1); !iterator_equal(it_m, multimap_end(pmmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_first(iterator_get_pointer(it_m)));
    }
    printf("\n");
    printf("The original multimapped values of m1 =");
    for(it_m = multimap_begin(pmmap_m1); !iterator_equal(it_m, multimap_end(pmmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    pair_make(ppair_p, 1, 10);
    it_m = multimap_insert(pmmap_m1, ppair_p);
    if(!iterator_equal(it_m, multimap_end(pmmap_m1)))
    {
        printf("The element 10 was inserted in m1 successfully.\n");
    }
    else
    {
        printf("The number 1 already exists in m1.\n");
    }

    /* The hint version of insert */
    pair_make(ppair_p, 5, 50);
    multimap_insert_hint(pmmap_m1, iterator_prev(multimap_end(pmmap_m1)), ppair_p);
    printf("After the insertions, the key values of m1 =");
    for(it_m = multimap_begin(pmmap_m1); !iterator_equal(it_m, multimap_end(pmmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_first(iterator_get_pointer(it_m)));
    }
    printf("\n");
    printf("and multimapped values of m1 =");
    for(it_m = multimap_begin(pmmap_m1); !iterator_equal(it_m, multimap_end(pmmap_m1)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    pair_make(ppair_p, 10, 100);
    multimap_insert(pmmap_m2, ppair_p);
    /* The templatized version inserting a range */
    multimap_insert_range(pmmap_m2, iterator_next(multimap_begin(pmmap_m1)), iterator_prev(multimap_end(pmmap_m1)));
    printf("After the insertions, the key values of m2 =");
    for(it_m = multimap_begin(pmmap_m2); !iterator_equal(it_m, multimap_end(pmmap_m2)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_first(iterator_get_pointer(it_m)));
    }
    printf("\n");
    printf("and multimapped values of m2 =");
    for(it_m = multimap_begin(pmmap_m2); !iterator_equal(it_m, multimap_end(pmmap_m2)); it_m = iterator_next(it_m))
    {
        printf(" %d", *(int*)pair_second(iterator_get_pointer(it_m)));
    }
    printf("\n");

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);
    multimap_destroy(pmmap_m2);

    return 0;
}
