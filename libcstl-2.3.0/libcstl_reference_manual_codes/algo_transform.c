/*
 * algo_transform.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

static void _mult_valu_2(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_input * 2;
}

static void _mult_valu_5(const void* cpv_input, void* pv_output)
{
    *(int*)pv_output = *(int*)cpv_input * 5;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_iterator_t it_v;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init_n(pvec_v2, 7);
    vector_init_n(pvec_v3, 7);

    for(i = -4; i <= 2; ++i)
    {
        vector_push_back(pvec_v1, i);
    }

    printf("Original vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Modifying the vector v1 in place */
    algo_transform(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v1), _mult_valu_2);
    printf("The elements of the vector v1 multiplied by 2 in place is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Using transform to multiply each element by a factor of 5 */
    algo_transform(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v2), _mult_valu_5);
    printf("Mutiplying the elements of the vector v2 by factor 5 is ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* 
     * The second version of transform used to multiply the 
     * elements of the vectors v1 and v2 pairwise
     */
    algo_transform_binary(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v2), vector_begin(pvec_v3), fun_multiplies_int);
    printf("Mutiplying the elements of the vector v3 is ( ");
    for(it_v = vector_begin(pvec_v3);
        !iterator_equal(it_v, vector_end(pvec_v3));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);

    return 0;
}
