/*
 * deque_equal.c
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
    deque_push_back(pdq_q2, 1);

    if(deque_equal(pdq_q1, pdq_q2))
    {
        printf("The deques are equal.\n");
    }
    else
    {
        printf("The deques are not equal.\n");
    }

    deque_push_back(pdq_q1, 1);
    if(deque_equal(pdq_q1, pdq_q2))
    {
        printf("The deques are equal.\n");
    }
    else
    {
        printf("The deques are not equal.\n");
    }

    deque_destroy(pdq_q1);
    deque_destroy(pdq_q2);

    return 0;
}
