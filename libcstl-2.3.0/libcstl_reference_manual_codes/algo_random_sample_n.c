/*
 * algo_random_sample_n.c
 * compile with : -lcslt
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    deque_t* pdeq_dq1 = create_deque(int);
    deque_iterator_t it_dq;
    int i = 0;

    if(pvec_v1 == NULL || pdeq_dq1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    deque_init_n(pdeq_dq1, 20);

    for(i = 0; i < 15; ++i)
    {
        vector_push_back(pvec_v1, i);
    }

    printf("The original vector v1 is: ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    algo_random_sample_n(vector_begin(pvec_v1), vector_end(pvec_v1),
        deque_begin(pdeq_dq1), 10);

    printf("The random sample 10 dq1 is : ( ");
    for(it_dq = deque_begin(pdeq_dq1);
        !iterator_equal(it_dq, deque_end(pdeq_dq1));
        it_dq = iterator_next(it_dq))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_dq));
    }
    printf(")\n");

    algo_random_sample_n(vector_begin(pvec_v1), vector_end(pvec_v1),
        deque_begin(pdeq_dq1), 20);

    printf("The random sample 20 dq1 is : ( ");
    for(it_dq = deque_begin(pdeq_dq1);
        !iterator_equal(it_dq, deque_end(pdeq_dq1));
        it_dq = iterator_next(it_dq))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_dq));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    deque_destroy(pdeq_dq1);

    return 0;
}
