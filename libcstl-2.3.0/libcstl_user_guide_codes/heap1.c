/*
 * heap1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

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

    for(i = 3; i <= 7; ++i)
    {
        vector_push_back(pvec_coll, i);
    }
    for(i = 5; i <= 9; ++i)
    {
        vector_push_back(pvec_coll, i);
    }
    for(i = 1; i <= 4; ++i)
    {
        vector_push_back(pvec_coll, i);
    }

    printf("on entry: ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_make_heap(vector_begin(pvec_coll), vector_end(pvec_coll));
    printf("after algo_make_heap(): ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_pop_heap(vector_begin(pvec_coll), vector_end(pvec_coll));
    vector_pop_back(pvec_coll);
    printf("after algo_pop_heap(): ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_push_back(pvec_coll, 17);
    algo_push_heap(vector_begin(pvec_coll), vector_end(pvec_coll));
    printf("after algo_push_heap(): ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_sort_heap(vector_begin(pvec_coll), vector_end(pvec_coll));
    printf("after algo_sort_heap(): ");
    for(it_pos = vector_begin(pvec_coll);
        !iterator_equal(it_pos, vector_end(pvec_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_coll);

    return 0;
}
