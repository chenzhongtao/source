/*
 * algo_is_sort.c
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

    printf("Original vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    if(algo_is_sorted(vector_begin(pvec_v1), vector_end(pvec_v1)))
    {
        printf("Vector is sorted with predicate less than.\n");
    }
    else
    {
        printf("Vector is not sorted with predicate less than.\n");
    }
    if(algo_is_sorted_if(vector_begin(pvec_v1), vector_end(pvec_v1), fun_greater_int))
    {
        printf("Vector is sorted with predicate greater than.\n");
    }
    else
    {
        printf("Vector is not sorted with predicate greater than.\n");
    }

    algo_sort(vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("Sorted vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    if(algo_is_sorted(vector_begin(pvec_v1), vector_end(pvec_v1)))
    {
        printf("Vector is sorted with predicate less than.\n");
    }
    else
    {
        printf("Vector is not sorted with predicate less than.\n");
    }
    if(algo_is_sorted_if(vector_begin(pvec_v1), vector_end(pvec_v1), fun_greater_int))
    {
        printf("Vector is sorted with predicate greater than.\n");
    }
    else
    {
        printf("Vector is not sorted with predicate greater than.\n");
    }

    /* To sort in descending order. */
    algo_sort_if(vector_begin(pvec_v1), vector_end(pvec_v1), fun_greater_int);
    printf("Resorted (greater) vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    if(algo_is_sorted(vector_begin(pvec_v1), vector_end(pvec_v1)))
    {
        printf("Vector is sorted with predicate less than.\n");
    }
    else
    {
        printf("Vector is not sorted with predicate less than.\n");
    }
    if(algo_is_sorted_if(vector_begin(pvec_v1), vector_end(pvec_v1), fun_greater_int))
    {
        printf("Vector is sorted with predicate greater than.\n");
    }
    else
    {
        printf("Vector is not sorted with predicate greater than.\n");
    }

    vector_destroy(pvec_v1);

    return 0;
}
