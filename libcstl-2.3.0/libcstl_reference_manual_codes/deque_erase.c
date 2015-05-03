/*
 * deque_erase.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int);
    deque_iterator_t it_q;

    if(pdq_q1 == NULL)
    {
        return -1;
    }

    deque_init(pdq_q1);

    deque_push_back(pdq_q1, 10);
    deque_push_back(pdq_q1, 20);
    deque_push_back(pdq_q1, 30);
    deque_push_back(pdq_q1, 40);
    deque_push_back(pdq_q1, 50);

    printf("The initial deque is: ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_erase(pdq_q1, deque_begin(pdq_q1));
    printf("After erasing the first element, the deque becomes: ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_erase_range(pdq_q1, iterator_next(deque_begin(pdq_q1)), deque_end(pdq_q1));
    printf("After erasing all elements but the first, the deque becomes: ");
    for(it_q = deque_begin(pdq_q1); !iterator_equal(it_q, deque_end(pdq_q1)); it_q = iterator_next(it_q))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_q));
    }
    printf("\n");

    deque_destroy(pdq_q1);

    return 0;
}
