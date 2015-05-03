/*
 * deque_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q0 = create_deque(int);
    deque_t* pdq_q1 = create_deque(int);
    deque_t* pdq_q2 = create_deque(int);
    deque_t* pdq_q3 = create_deque(int);
    deque_t* pdq_q4 = create_deque(int);
    deque_iterator_t it_q;

    if(pdq_q0 == NULL || pdq_q1 == NULL || pdq_q2 == NULL || pdq_q3 == NULL || pdq_q4 == NULL)
    {
        return -1;
    }

    /* Create an empty deque q0 */
    deque_init(pdq_q0);

    /* Create a deque q1 with 3 elements of default value 0 */
    deque_init_n(pdq_q1, 3);

    /* Create a deque q2 with 5 elements of value 2 */
    deque_init_elem(pdq_q2, 5, 2);

    /* Create a copy, deque q3, of deque q2 */
    deque_init_copy(pdq_q3, pdq_q2);

    /* Create a deque q4 by copying the range q3[first, last) */
    deque_init_copy_range(pdq_q4, deque_begin(pdq_q3), iterator_advance(deque_begin(pdq_q3), 2));

    printf("q1 = ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    printf("q2 = ");
    for(it_q = deque_begin(pdq_q2); !iterator_equal(it_q, deque_end(pdq_q2)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    printf("q3 = ");
    for(it_q = deque_begin(pdq_q3); !iterator_equal(it_q, deque_end(pdq_q3)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    printf("q4 = ");
    for(it_q = deque_begin(pdq_q4); !iterator_equal(it_q, deque_end(pdq_q4)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_destroy(pdq_q0);
    deque_destroy(pdq_q1);
    deque_destroy(pdq_q2);
    deque_destroy(pdq_q3);
    deque_destroy(pdq_q4);

    return 0;
}
