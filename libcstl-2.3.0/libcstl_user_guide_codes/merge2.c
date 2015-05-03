/*
 * merge2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll1 = create_vector(int);
    list_t* plist_coll2 = create_list(int);
    iterator_t it_pos;
    iterator_t it_bound;
    int i = 0;

    if(pvec_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    list_init(plist_coll2);

    for(i = 4; i <= 9; ++i)
    {
        vector_push_back(pvec_coll1, i);
    }
    for(i = 1; i <= 7; ++i)
    {
        vector_push_back(pvec_coll1, i);
    }

    for(i = 6; i >= 2; --i)
    {
        list_push_back(plist_coll2, i);
    }
    for(i = 9; i >= 4; --i)
    {
        list_push_back(plist_coll2, i);
    }

    printf("coll1: ");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_bound = algo_find(vector_begin(pvec_coll1), vector_end(pvec_coll1), 1);
    algo_inplace_merge(vector_begin(pvec_coll1), it_bound, vector_end(pvec_coll1));
    printf("coll1: ");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_bound = algo_find(list_begin(plist_coll2), list_end(plist_coll2), 9);
    algo_inplace_merge_if(list_begin(plist_coll2), it_bound,
        list_end(plist_coll2), fun_greater_int);
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_coll1);
    list_destroy(plist_coll2);

    return 0;
}
