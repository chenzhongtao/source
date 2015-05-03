/*
 * algo_copy_backward.c
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

    for(i = 0; i < 6; ++i)
    {
        vector_push_back(pvec_v1, i * 10);
    }
    for(i = 0; i < 11; ++i)
    {
        vector_push_back(pvec_v2, i * 3);
    }

    printf("v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To copy the first 3 elements of v1 into the middle of v2 */
    algo_copy_backward(vector_begin(pvec_v1), iterator_next_n(vector_begin(pvec_v1), 3),
        iterator_next_n(vector_begin(pvec_v2), 7));
    printf("v2 with v1 insert = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To shift the elements inserted into v2 two positions to the left */
    algo_copy_backward(iterator_next_n(vector_begin(pvec_v2), 4),
        iterator_next_n(vector_begin(pvec_v2), 7),
        iterator_next_n(vector_begin(pvec_v2), 9));
    printf("v2 with shifted insert = ( ");
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
