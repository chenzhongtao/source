/*
 * fun_divides.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(double);
    vector_t* pvec_v2 = create_vector(double);
    vector_t* pvec_v3 = create_vector(double);
    iterator_t it_pos;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    vector_init_n(pvec_v3, 6);

    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 7.0);
    }
    for(i = 1; i <= 6; ++i)
    {
        vector_push_back(pvec_v2, i * 2.0);
    }

    printf("The vector v1 = ");
    for(it_pos = vector_begin(pvec_v1);
        !iterator_equal(it_pos, vector_end(pvec_v1));
        it_pos = iterator_next(it_pos))
    {
        printf("%lf ", *(double*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("The vector v2 = ");
    for(it_pos = vector_begin(pvec_v2);
        !iterator_equal(it_pos, vector_end(pvec_v2));
        it_pos = iterator_next(it_pos))
    {
        printf("%lf ", *(double*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_transform_binary(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v2), vector_begin(pvec_v3), fun_divides_double);

    printf("The element-wise quotients are: ");
    for(it_pos = vector_begin(pvec_v3);
        !iterator_equal(it_pos, vector_end(pvec_v3));
        it_pos = iterator_next(it_pos))
    {
        printf("%lf ", *(double*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);

    return 0;
}