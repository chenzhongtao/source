/*
 * partsum1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    vector_t* pvec_coll2 = create_vector(int);
    iterator_t it_pos;

    if(plist_coll1 == NULL || pvec_coll2 == NULL)
    {
        return -1;
    }

    list_init_n(plist_coll1, 6);
    vector_init_n(pvec_coll2, list_size(plist_coll1));

    algo_iota(list_begin(plist_coll1), list_end(plist_coll1), 1);
    for(it_pos = list_begin(plist_coll1);
        !iterator_equal(it_pos, list_end(plist_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_partial_sum(list_begin(plist_coll1),
        list_end(plist_coll1), vector_begin(pvec_coll2));
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, vector_end(pvec_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_partial_sum_if(list_begin(plist_coll1), list_end(plist_coll1),
        vector_begin(pvec_coll2), fun_multiplies_int);
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, vector_end(pvec_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll1);
    vector_destroy(pvec_coll2);

    return 0;
}
