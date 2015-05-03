/*
 * algo_swap_ranges.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    deque_t* pdeq_q1 = create_deque(int);
    deque_iterator_t it_q;
    int i = 0;

    if(pvec_v1 == NULL || pdeq_q1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    deque_init(pdeq_q1);

    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 4; i <= 9; ++i)
    {
        deque_push_back(pdeq_q1, 6);
    }

    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    printf("Deque q1 is ( ");
    for(it_q = deque_begin(pdeq_q1);
        !iterator_equal(it_q, deque_end(pdeq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf(")\n");

    algo_swap_ranges(vector_begin(pvec_v1), vector_end(pvec_v1), deque_begin(pdeq_q1));

    printf("After the swap_range, vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    printf("After the swap_range, deque q1 is ( ");
    for(it_q = deque_begin(pdeq_q1);
        !iterator_equal(it_q, deque_end(pdeq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    deque_destroy(pdeq_q1);

    return 0;
}
