/*
 * deque_push_front.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int);

    if(pdq_q1 == NULL)
    {
        return -1;
    }

    deque_init(pdq_q1);

    deque_push_front(pdq_q1, 1);
    if(deque_size(pdq_q1) != 0)
    {
        printf("First element: %d\n", *(int*)deque_front(pdq_q1));
    }

    deque_push_front(pdq_q1, 2);
    if(deque_size(pdq_q1) != 0)
    {
        printf("New first element: %d\n", *(int*)deque_front(pdq_q1));
    }

    deque_destroy(pdq_q1);

    return 0;
}
