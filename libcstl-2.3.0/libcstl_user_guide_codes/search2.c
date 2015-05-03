/*
 * search2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _check_even(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    if(*(bool_t*)cpv_second)
    {
        *(bool_t*)pv_output = *(int*)cpv_first % 2 == 0 ? true : false;
    }
    else
    {
        *(bool_t*)pv_output = *(int*)cpv_first % 2 == 1 ? true : false;
    }
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    vector_t* pvec_subcoll = create_vector(bool_t);
    iterator_t it_pos;
    int i = 0;

    if(pvec_coll == NULL || pvec_subcoll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);
    vector_init(pvec_subcoll);

    for(i = 1; i <= 9; ++i)
    {
        vector_push_back(pvec_coll, i);
    }
    vector_push_back(pvec_subcoll, true);
    vector_push_back(pvec_subcoll, false);
    vector_push_back(pvec_subcoll, true);

    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_pos = algo_search_if(vector_begin(pvec_coll), vector_end(pvec_coll),
        vector_begin(pvec_subcoll), vector_end(pvec_subcoll), _check_even);
    while(!iterator_equal(it_pos, vector_end(pvec_coll)))
    {
        printf("subcoll found starting with element %d\n",
            iterator_distance(vector_begin(pvec_coll), it_pos) + 1);

        it_pos = algo_search_if(iterator_next(it_pos), vector_end(pvec_coll),
            vector_begin(pvec_subcoll), vector_end(pvec_subcoll), _check_even);
    }

    vector_destroy(pvec_coll);
    vector_destroy(pvec_subcoll);

    return 0;
}
