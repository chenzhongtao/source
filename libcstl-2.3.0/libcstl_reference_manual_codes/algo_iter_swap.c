/*
 * algo_iter_swap.c
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
    deque_t* pdq_dq1 = create_deque(int);
    deque_t* pdq_dq2 = create_deque(int);
    deque_iterator_t it_dq;
    int i = 0;

    if(pvec_v1 == NULL || pdq_dq1 == NULL || pdq_dq2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    deque_init(pdq_dq1);
    deque_init(pdq_dq2);

    deque_push_back(pdq_dq1, 5);
    deque_push_back(pdq_dq1, 1);
    deque_push_back(pdq_dq1, 10);

    printf("The original deque dq1 = ( ");
    for(it_dq = deque_begin(pdq_dq1);
        !iterator_equal(it_dq, deque_end(pdq_dq1));
        it_dq = iterator_next(it_dq))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_dq));
    }
    printf(")\n");

    /* Exchanging first and last elements with iter_swap */
    algo_iter_swap(deque_begin(pdq_dq1), iterator_prev(deque_end(pdq_dq1)));

    printf("The deque dq1 with first and last element swap is = ( ");
    for(it_dq = deque_begin(pdq_dq1);
        !iterator_equal(it_dq, deque_end(pdq_dq1));
        it_dq = iterator_next(it_dq))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_dq));
    }
    printf(")\n");

    /* Swapping the second and last elements with swap */
    algo_swap(iterator_prev(deque_end(pdq_dq1)), iterator_next(deque_begin(pdq_dq1)));

    printf("The deque dq1 with the second and last element swap is = ( ");
    for(it_dq = deque_begin(pdq_dq1);
        !iterator_equal(it_dq, deque_end(pdq_dq1));
        it_dq = iterator_next(it_dq))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_dq));
    }
    printf(")\n");

    /* Swapping a vector element with a deque element */
    for(i = 0; i < 4; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 4; i < 6; ++i)
    {
        deque_push_back(pdq_dq2, i);
    }

    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("Deque dq2 is ( ");
    for(it_dq = deque_begin(pdq_dq2);
        !iterator_equal(it_dq, deque_end(pdq_dq2));
        it_dq = iterator_next(it_dq))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_dq));
    }
    printf(")\n");

    algo_iter_swap(vector_begin(pvec_v1), deque_begin(pdq_dq2));

    printf("After exchanging first elements:\n");
    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("Deque dq2 is ( ");
    for(it_dq = deque_begin(pdq_dq2);
        !iterator_equal(it_dq, deque_end(pdq_dq2));
        it_dq = iterator_next(it_dq))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_dq));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    deque_destroy(pdq_dq1);
    deque_destroy(pdq_dq2);

    return 0;
}
