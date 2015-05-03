/*
 * algo_partial_sort.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    int i = 0;

    if(pvec_v1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);

    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 2);
    }
    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i * 2 + 1);
    }

    printf("Original vector:\nv1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    algo_partial_sort(vector_begin(pvec_v1),
        iterator_next_n(vector_begin(pvec_v1), 6), vector_end(pvec_v1));
    printf("Partially sorted vector:\nv1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To partially sort in descending order, specify binary predicate */
    algo_partial_sort_if(vector_begin(pvec_v1),
        iterator_next_n(vector_begin(pvec_v1), 8),
        vector_end(pvec_v1), fun_greater_int);
    printf("Partially resorted (greater) vector:\nv1 = ( ");
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
