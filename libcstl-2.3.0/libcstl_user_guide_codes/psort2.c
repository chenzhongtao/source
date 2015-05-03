/*
 * psort2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll = create_deque(int);
    vector_t* pvec_coll6 = create_vector(int);
    vector_t* pvec_coll30 = create_vector(int);
    iterator_t it_pos;
    iterator_t it_end;
    int i = 0;

    if(pdeq_coll == NULL || pvec_coll6 == NULL || pvec_coll30 == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);
    vector_init_n(pvec_coll6, 6);
    vector_init_n(pvec_coll30, 30);

    for(i = 3; i <= 7; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(i = 2; i <= 6; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(i = 1; i <= 5; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_end = algo_partial_sort_copy(deque_begin(pdeq_coll), deque_end(pdeq_coll),
        vector_begin(pvec_coll6), vector_end(pvec_coll6));
    for(it_pos = vector_begin(pvec_coll6);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_end = algo_partial_sort_copy_if(deque_begin(pdeq_coll), deque_end(pdeq_coll),
        vector_begin(pvec_coll30), vector_end(pvec_coll30), fun_greater_int);
    for(it_pos = vector_begin(pvec_coll30);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    deque_destroy(pdeq_coll);
    vector_destroy(pvec_coll6);
    vector_destroy(pvec_coll30);

    return 0;
}
