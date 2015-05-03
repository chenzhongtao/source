/*
 * equal1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _both_even_or_odd(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first % 2 == *(int*)cpv_second % 2 ?
        true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll1 = create_vector(int);
    list_t* plist_coll2 = create_list(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    list_init(plist_coll2);

    for(i = 1; i <= 7; ++i)
    {
        vector_push_back(pvec_coll1, i);
    }
    for(i = 3; i <= 9; ++i)
    {
        list_push_back(plist_coll2, i);
    }

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

    if(algo_equal(vector_begin(pvec_coll1),
        vector_end(pvec_coll1), list_begin(plist_coll2)))
    {
        printf("coll1 == coll2\n");
    }
    else
    {
        printf("coll1 != coll2\n");
    }

    if(algo_equal_if(vector_begin(pvec_coll1), vector_end(pvec_coll1),
        list_begin(plist_coll2), _both_even_or_odd))
    {
        printf("even and odd elements correspond\n");
    }
    else
    {
        printf("even and odd elements do not correspond\n");
    }

    vector_destroy(pvec_coll1);
    list_destroy(plist_coll2);

    return 0;
}
