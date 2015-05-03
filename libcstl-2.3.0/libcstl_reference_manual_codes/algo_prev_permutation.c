/*
 * algo_prev_permutation.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/cdeque.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ? true : false;
}

int main(int argc, char* argv[])
{
    deque_t* pdeq_q1 = create_deque(int);
    deque_iterator_t it_q;
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    bool_t b_result = false;
    int i = 0;

    if(pdeq_q1 == NULL || pvec_v1 == NULL)
    {
        return -1;
    }

    deque_init(pdeq_q1);
    vector_init(pvec_v1);

    deque_push_back(pdeq_q1, 5);
    deque_push_back(pdeq_q1, 1);
    deque_push_back(pdeq_q1, 10);

    printf("The original deque of q1 = ( ");
    for(it_q = deque_begin(pdeq_q1);
        !iterator_equal(it_q, deque_end(pdeq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf(")\n");

    b_result = algo_prev_permutation(deque_begin(pdeq_q1), deque_end(pdeq_q1));
    if(b_result)
    {
        printf("The lexicographically next permutation exists and has\n"
               "replaced the original ordering of the sequence in q1.\n");
    }
    else
    {
        printf("The lexicographically next permutation doesn't exists and\n"
               "the lexicographically smallest permutation has replaced the\n"
               "original ordering of the sequence in q1.\n");
    }
    printf("After one application of prev_permutation q1 = ( ");
    for(it_q = deque_begin(pdeq_q1);
        !iterator_equal(it_q, deque_end(pdeq_q1));
        it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf(")\n");

    for(i = -3; i <= 3; ++i)
    {
        vector_push_back(pvec_v1, i);
    }

    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    algo_prev_permutation_if(vector_begin(pvec_v1),
        vector_end(pvec_v1), _mod_lesser);
    printf("After the first prev_permutation, vector v1 is:\n( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    for(i = 1; i <= 5; ++i)
    {
        algo_prev_permutation_if(vector_begin(pvec_v1),
            vector_end(pvec_v1), _mod_lesser);
        printf("After another prev_permutation, vector v1 is:\n( ");
        for(it_v = vector_begin(pvec_v1);
            !iterator_equal(it_v, vector_end(pvec_v1));
            it_v = iterator_next(it_v))
        {
            printf("%d ", *(int*)iterator_get_pointer(it_v));
        }
        printf(")\n");
    }

    deque_destroy(pdeq_q1);
    vector_destroy(pvec_v1);

    return 0;
}
