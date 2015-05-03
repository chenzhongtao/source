/*
 * algo_power.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL)
    {
        return -1;
    }

    vector_init_n(pvec_v1, 10);
    vector_init_n(pvec_v2, 10);

    algo_iota(vector_begin(pvec_v1), vector_end(pvec_v1), 1);

    /* The first function for power */
    printf("The original vector v1 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    for(it_v = vector_begin(pvec_v1), i = 0;
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v), ++i)
    {
        algo_power(it_v, 3, vector_at(pvec_v2, i));
    }

    printf("The power result vector v2 is:\n( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* The second function for multiplus */
    for(it_v = vector_begin(pvec_v1), i = 0;
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v), ++i)
    {
        algo_power_if(it_v, 3, fun_plus_int, vector_at(pvec_v2, i));
    }

    printf("The multiplus result vector v2 is:\n( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);

    return 0;
}
