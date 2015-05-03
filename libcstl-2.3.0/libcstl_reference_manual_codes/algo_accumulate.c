/*
 * algo_accumulate.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_vec1 = create_vector(int);
    vector_t* pvec_vec2 = create_vector(int);
    vector_t* pvec_vec3 = create_vector(int);
    vector_t* pvec_vec4 = create_vector(int);
    vector_iterator_t it_vec;
    int n_sum = 0;
    int n_product = 0;
    int i = 0;

    if(pvec_vec1 == NULL || pvec_vec2 == NULL ||
       pvec_vec3 == NULL || pvec_vec4 == NULL)
    {
        return -1;
    }

    /* The first function for the accumulated sums */
    vector_init(pvec_vec1);
    for(i = 1; i < 21; ++i)
    {
        vector_push_back(pvec_vec1, i);
    }
    vector_init_n(pvec_vec2, vector_size(pvec_vec1));

    printf("The original vector vec1 is:\n( ");
    for(it_vec = vector_begin(pvec_vec1);
        !iterator_equal(it_vec, vector_end(pvec_vec1));
        it_vec = iterator_next(it_vec))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_vec));
    }
    printf(")\n");

    algo_accumulate(vector_begin(pvec_vec1), vector_end(pvec_vec1), 0, &n_sum);
    printf("The sum of the integers from 1 to 20 is: %d\n", n_sum);

    /* Construction a vector of partial sums */
    for(it_vec = vector_begin(pvec_vec1), i = 0;
        !iterator_equal(it_vec, vector_end(pvec_vec1));
        it_vec = iterator_next(it_vec), ++i)
    {
        algo_accumulate(vector_begin(pvec_vec1), iterator_next(it_vec),
            0, vector_at(pvec_vec2, i));
    }

    printf("The vector of partial sums is:\n( ");
    for(it_vec = vector_begin(pvec_vec2);
        !iterator_equal(it_vec, vector_end(pvec_vec2));
        it_vec = iterator_next(it_vec))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_vec));
    }
    printf(")\n");

    vector_destroy(pvec_vec1);
    vector_destroy(pvec_vec2);

    /* The second function for the accumulated product */
    vector_init(pvec_vec3);
    for(i = 1; i < 11; ++i)
    {
        vector_push_back(pvec_vec3, i);
    }
    vector_init_n(pvec_vec4, vector_size(pvec_vec3));

    printf("The original vector vec3 is:\n( ");
    for(it_vec = vector_begin(pvec_vec3);
        !iterator_equal(it_vec, vector_end(pvec_vec3));
        it_vec = iterator_next(it_vec))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_vec));
    }
    printf(")\n");

    algo_accumulate_if(vector_begin(pvec_vec3), vector_end(pvec_vec3),
        1, fun_multiplies_int, &n_product);
    printf("The product of the integers from 1 to 10 is: %d.\n", n_product);

    /* Constructing a vector of partial products */
    for(it_vec = vector_begin(pvec_vec3), i = 0;
        !iterator_equal(it_vec, vector_end(pvec_vec3));
        it_vec = iterator_next(it_vec), ++i)
    {
        algo_accumulate_if(vector_begin(pvec_vec3), iterator_next(it_vec),
            1, fun_multiplies_int, vector_at(pvec_vec4, i));
    }

    printf("The vector of partial products is:\n( ");
    for(it_vec = vector_begin(pvec_vec4);
        !iterator_equal(it_vec, vector_end(pvec_vec4));
        it_vec = iterator_next(it_vec))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_vec));
    }
    printf(")\n");

    vector_destroy(pvec_vec3);
    vector_destroy(pvec_vec4);

    return 0;
}
