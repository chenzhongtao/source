/*
 * adjfind1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

/*
 * return whether the second data has double the value of the first.
 */
static void _doubled(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first * 2 == *(int*)cpv_second ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    vector_iterator_t it_pos;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    vector_push_back(pvec_coll, 1);
    vector_push_back(pvec_coll, 3);
    vector_push_back(pvec_coll, 2);
    vector_push_back(pvec_coll, 4);
    vector_push_back(pvec_coll, 5);
    vector_push_back(pvec_coll, 5);
    vector_push_back(pvec_coll, 0);

    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* search first two elements with equal values */
    it_pos = algo_adjacent_find(vector_begin(pvec_coll), vector_end(pvec_coll));
    if(!iterator_equal(it_pos, vector_end(pvec_coll)))
    {
        printf("first two elements with equal value have position %d\n",
            iterator_distance(vector_begin(pvec_coll), it_pos) + 1);
    }

    /* 
     * search first two elements for which
     * the second has double the value of the first
     */
    it_pos = algo_adjacent_find_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), _doubled);
    if(!iterator_equal(it_pos, vector_end(pvec_coll)))
    {
        printf("first two elements with second value twice the first has pos %d\n",
            iterator_distance(vector_begin(pvec_coll), it_pos) + 1);
    }

    vector_destroy(pvec_coll);

    return 0;
}
