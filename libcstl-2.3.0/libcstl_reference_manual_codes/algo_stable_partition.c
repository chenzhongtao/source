/*
 * algo_stable_partition.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _greater_5(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 5 ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    vector_iterator_t it_result;
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = 0; i <= 10; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 0; i <= 4; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    algo_random_shuffle(vector_begin(pvec_v1), vector_end(pvec_v1));

    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Partition the range with predicate greater5 */
    it_result = algo_stable_partition(
        vector_begin(pvec_v1), vector_end(pvec_v1), _greater_5);

    printf("The partitioned set of elements in v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    printf("The first element in v1 to fail to satisfy "
           "the predicate greater 5 is : %d\n",
           *(int*)iterator_get_pointer(it_result));

    vector_destroy(pvec_v1);

    return 0;
}
