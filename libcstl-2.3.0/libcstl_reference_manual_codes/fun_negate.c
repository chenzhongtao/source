/*
 * fun_negate.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init_n(pvec_v2, 8);

    for(i = -2; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
    }

    printf("The vector v1 = ");
    for(it_pos = vector_begin(pvec_v1);
        !iterator_equal(it_pos, vector_end(pvec_v1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_transform(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v2), fun_negate_int);

    printf("The negated element of the vector = ");
    for(it_pos = vector_begin(pvec_v2);
        !iterator_equal(it_pos, vector_end(pvec_v2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);

    return 0;
}
