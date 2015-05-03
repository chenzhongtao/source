/*
 * find3.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _greater_3(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 3 ? true : false;
}

static void _divisible_3(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input % 3 == 0 ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    vector_iterator_t it_pos;
    int i = 0;

    if(pvec_coll == 0)
    {
        return -1;
    }

    vector_init(pvec_coll);

    for(i = 1; i <= 9; ++i)
    {
        vector_push_back(pvec_coll, i);
    }
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* find first element greater than 3 */
    it_pos = algo_find_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), _greater_3);

    /* print its posititon */
    printf("the %d. element is the first greater than 3.\n",
        iterator_distance(vector_begin(pvec_coll), it_pos) + 1);

    /* find first element divisible by 3 */
    it_pos = algo_find_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), _divisible_3);

    /* print its position */
    printf("the %d. element is the first divisible by 3.\n",
        iterator_distance(vector_begin(pvec_coll), it_pos) + 1);

    vector_destroy(pvec_coll);

    return 0;
}
