/*
 * algo_remove_copy.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

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

    vector_init(pvec_v1);
    vector_init(pvec_v2);

    for(i = 0; i < 10; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 0; i < 4; ++i)
    {
        vector_push_back(pvec_v1, 7);
    }

    algo_random_shuffle(vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("The original vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_resize(pvec_v2, vector_size(pvec_v1));
    it_v = algo_remove_copy(vector_begin(pvec_v1), vector_end(pvec_v1), vector_begin(pvec_v2), 7);

    printf("Vector v1 is left unchanged as ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("Vector v2 is a copy of v1 with the value 7 removed ( ");
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
