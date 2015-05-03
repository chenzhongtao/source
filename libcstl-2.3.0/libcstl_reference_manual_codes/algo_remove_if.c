/*
 * algo_remove_if.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _greater_6(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 6 ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    vector_iterator_t it_end;
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = 0; i <= 9; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 0; i <= 3; ++i)
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

    /* Remove elements satisfying predicate greater5 */
    it_end = algo_remove_if(vector_begin(pvec_v1), vector_end(pvec_v1), _greater_6);

    printf("Vector v1 with elements satisfying greater6 removed is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To change the sequence size, use erase */
    vector_erase_range(pvec_v1, it_end, vector_end(pvec_v1));

    printf("Vector v1 resized elements satisfying greater6 removed is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_destroy(pvec_v1);

    return 0;
}
