/*
 * deque_greater.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int);
    deque_t* pdq_q2 = create_deque(int);

    if(pdq_q1 == NULL || pdq_q2 == NULL)
    {
        return -1;
    }

    deque_init(pdq_q1);
    deque_init(pdq_q2);

    deque_push_back(pdq_q1, 1);
    deque_push_back(pdq_q1, 3);
    deque_push_back(pdq_q1, 1);

    deque_push_back(pdq_q2, 1);
    deque_push_back(pdq_q2, 2);
    deque_push_back(pdq_q2, 2);

    if(deque_greater(pdq_q1, pdq_q2))
    {
        printf("Deque q1 is greater than deque q2.\n");
    }
    else
    {
        printf("Deque q1 is not greater than deque q2.\n");
    }

    deque_destroy(pdq_q1);
    deque_destroy(pdq_q2);

    return 0;
}
