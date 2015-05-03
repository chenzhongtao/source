/*
 * algo_sort_heap.c
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

    for(i = 1; i <= 9; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    algo_random_shuffle(vector_begin(pvec_v1), vector_end(pvec_v1));

    printf("Vector v1 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Make v1 a heap with default less than ordering */
    algo_make_heap(vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("The heap version of vector v1 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Sort heap v1 with default less-than ordering */
    algo_sort_heap(vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("The heap v1 becomes the sorted range:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Make v1 a heap with greater than ordering */
    algo_make_heap_if(vector_begin(pvec_v1), vector_end(pvec_v1), fun_greater_int);
    printf("The greater-than heaped version of vector v1 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    algo_sort_heap_if(vector_begin(pvec_v1), vector_end(pvec_v1), fun_greater_int);
    printf("The greater-than heap v1 becomes the sorted range:\n( ");
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
