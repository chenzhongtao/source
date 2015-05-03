/*
 * misma1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll1 = create_vector(int);
    list_t* plist_coll2 = create_list(int);
    iterator_t it_pos;
    range_t t_result;
    int i = 0;

    if(pvec_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    list_init(plist_coll2);

    for(i = 1; i <= 6; ++i)
    {
        vector_push_back(pvec_coll1, i);
    }
    for(i = 1; i <= 16; i *= 2)
    {
        list_push_back(plist_coll2, i);
    }
    list_push_back(plist_coll2, 3);

    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    t_result = algo_mismatch(vector_begin(pvec_coll1),
        vector_end(pvec_coll1), list_begin(plist_coll2));
    if(iterator_equal(t_result.it_begin, vector_end(pvec_coll1)))
    {
        printf("no mismatch\n");
    }
    else
    {
        printf("first mismatch: %d and %d\n",
            *(int*)iterator_get_pointer(t_result.it_begin),
            *(int*)iterator_get_pointer(t_result.it_end));
    }

    t_result = algo_mismatch_if(vector_begin(pvec_coll1),
        vector_end(pvec_coll1), list_begin(plist_coll2), fun_less_equal_int);
    if(iterator_equal(t_result.it_begin, vector_end(pvec_coll1)))
    {
        printf("always less-or-equal\n");
    }
    else
    {
        printf("not less-or-equal: %d and %d\n",
            *(int*)iterator_get_pointer(t_result.it_begin),
            *(int*)iterator_get_pointer(t_result.it_end));
    }

    vector_destroy(pvec_coll1);
    list_destroy(plist_coll2);

    return 0;
}
