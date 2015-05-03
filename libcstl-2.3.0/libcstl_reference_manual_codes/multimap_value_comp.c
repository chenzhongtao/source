/*
 * multimap_value_comp.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cmap.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    multimap_t* pmmap_m1 = create_multimap(int, int);
    pair_t* ppair_p = create_pair(int, int);
    binary_function_t bfun_vc = NULL;
    bool_t b_result = false;
    multimap_iterator_t it_m1;
    multimap_iterator_t it_m2;

    if(pmmap_m1 == NULL || ppair_p == NULL)
    {
        return -1;
    }

    pair_init(ppair_p);
    multimap_init_ex(pmmap_m1, fun_less_int);

    pair_make(ppair_p, 1, 10);
    multimap_insert(pmmap_m1, ppair_p);
    pair_make(ppair_p, 2, 5);
    multimap_insert(pmmap_m1, ppair_p);

    it_m1 = multimap_find(pmmap_m1, 1);
    it_m2 = multimap_find(pmmap_m1, 2);
    bfun_vc = multimap_value_comp(pmmap_m1);

    (*bfun_vc)(iterator_get_pointer(it_m1), iterator_get_pointer(it_m2), &b_result);
    if(b_result)
    {
        printf("The element (1, 10) precedes the element (2, 5).\n");
    }
    else
    {
        printf("The element (1, 10) does not precedes the element (2, 5).\n");
    }

    (*bfun_vc)(iterator_get_pointer(it_m2), iterator_get_pointer(it_m1), &b_result);
    if(b_result)
    {
        printf("The element (2, 5) precedes the element (1, 10).\n");
    }
    else
    {
        printf("The element (2, 5) does not precedes the element (1, 10).\n");
    }

    pair_destroy(ppair_p);
    multimap_destroy(pmmap_m1);

    return 0;
}
