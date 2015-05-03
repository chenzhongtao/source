/*
 * issorted1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll = create_vector(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_coll == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll);

    for(i = 1; i <= 9; ++i)
    {
        vector_push_back(pvec_coll, i);
    }

    algo_random_shuffle(vector_begin(pvec_coll), vector_end(pvec_coll));
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    if(algo_is_sorted(vector_begin(pvec_coll), vector_end(pvec_coll)))
    {
        printf("coll is sorted with <.\n");
    }
    else
    {
        printf("coll is not sorted with <.\n");
    }
    if(algo_is_sorted_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), fun_greater_int))
    {
        printf("coll is sorted with >.\n");
    }
    else
    {
        printf("coll is not sorted with >.\n");
    }

    algo_sort(vector_begin(pvec_coll), vector_end(pvec_coll));
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    if(algo_is_sorted(vector_begin(pvec_coll), vector_end(pvec_coll)))
    {
        printf("coll is sorted with <.\n");
    }
    else
    {
        printf("coll is not sorted with <.\n");
    }
    if(algo_is_sorted_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), fun_greater_int))
    {
        printf("coll is sorted with >.\n");
    }
    else
    {
        printf("coll is not sorted with >.\n");
    }

    algo_sort_if(vector_begin(pvec_coll), vector_end(pvec_coll), fun_greater_int);
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    if(algo_is_sorted(vector_begin(pvec_coll), vector_end(pvec_coll)))
    {
        printf("coll is sorted with <.\n");
    }
    else
    {
        printf("coll is not sorted with <.\n");
    }
    if(algo_is_sorted_if(vector_begin(pvec_coll),
        vector_end(pvec_coll), fun_greater_int))
    {
        printf("coll is sorted with >.\n");
    }
    else
    {
        printf("coll is not sorted with >.\n");
    }

    vector_destroy(pvec_coll);

    return 0;
}
