/*
 * algo_generate_n.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstl/cvector.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

static void _random(const void* cpv_input, void* pv_output)
{
    srand((unsigned)time(NULL) + rand());
    *(int*)pv_output = rand();
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    deque_t* pdeq_q1 = create_deque(int);
    deque_iterator_t it_q;

    if(pvec_v1 == NULL || pdeq_q1 == NULL)
    {
        return -1;
    }

    vector_init_n(pvec_v1, 5);
    deque_init_n(pdeq_q1, 5);

    algo_generate_n(vector_begin(pvec_v1), 5, _random);
    printf("Vector v1 is ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    algo_generate_n(deque_begin(pdeq_q1), 3, _random);
    printf("Deque q1 is ( ");
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
