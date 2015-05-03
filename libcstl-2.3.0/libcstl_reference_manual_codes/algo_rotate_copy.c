/*
 * algo_rotate_copy.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v;
    deque_t* pdeq_q1 = create_deque(int);
    deque_t* pdeq_q2 = create_deque(int);
    deque_iterator_t it_q;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL ||
       pdeq_q1 == NULL || pdeq_q2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init_n(pvec_v2, 9);
    deque_init(pdeq_q1);
    deque_init_n(pdeq_q2, 6);

    for(i = -3; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = 0; i <= 5; ++i)
    {
        deque_push_back(pdeq_q1, i);
    }

    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    algo_rotate_copy(vector_begin(pvec_v1),
        iterator_next_n(vector_begin(pvec_v1), 3),
        vector_end(pvec_v1), vector_begin(pvec_v2));
    printf("After rotating, vector v2 is ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    printf("The original deque q1 is ( ");
    for(it_q = deque_begin(pdeq_q1);
        !iterator_equal(it_q, deque_end(pdeq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf(")\n");

    i = 1;
    while(i <= iterator_distance(deque_begin(pdeq_q1), deque_end(pdeq_q1)))
    {
        algo_rotate_copy(deque_begin(pdeq_q1),
            iterator_next(deque_begin(pdeq_q1)),
            deque_end(pdeq_q1), deque_begin(pdeq_q2));
        printf("After the rotation of a single deque element to the back q2 is ( ");
        for(it_q = deque_begin(pdeq_q2);
            !iterator_equal(it_q, deque_end(pdeq_q2));
            it_q = iterator_next(it_q))
        {
            printf("%d ", *(int*)iterator_get_pointer(it_q));
        }
        printf(")\n");
        i++;
    }

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    deque_destroy(pdeq_q1);
    deque_destroy(pdeq_q2);

    return 0;
}
