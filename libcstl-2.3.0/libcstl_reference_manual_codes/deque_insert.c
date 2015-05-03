/*
 * deque_insert.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int);
    deque_t* pdq_q2 = create_deque(int);
    deque_iterator_t it_q;

    if(pdq_q1 == NULL || pdq_q2 == NULL)
    {
        return -1;
    }

    deque_init(pdq_q1);
    deque_init(pdq_q2);

    deque_push_back(pdq_q1, 10);
    deque_push_back(pdq_q1, 20);
    deque_push_back(pdq_q1, 30);
    deque_push_back(pdq_q2, 40);
    deque_push_back(pdq_q2, 50);
    deque_push_back(pdq_q2, 60);

    printf("q1 = ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_insert(pdq_q1, iterator_next(deque_begin(pdq_q1)), 100);
    printf("q1 = ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_insert_n(pdq_q1, iterator_advance(deque_begin(pdq_q1), 2), 2, 200);
    printf("q1 = ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_insert_range(pdq_q1, iterator_next(deque_begin(pdq_q1)), deque_begin(pdq_q2), iterator_prev(deque_end(pdq_q2)));
    printf("q1 = ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_destroy(pdq_q1);
    deque_destroy(pdq_q2);

    return 0;
}
