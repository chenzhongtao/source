/*
 * deque_push_back.c
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

    deque_push_back(pdq_q1, 1);
    if(deque_size(pdq_q1) != 0)
    {
        printf("Last element: %d\n", *(int*)deque_back(pdq_q1));
    }

    deque_push_back(pdq_q1, 2);
    if(deque_size(pdq_q1) != 0)
    {
        printf("New last element: %d\n", *(int*)deque_back(pdq_q1));
    }

    deque_destroy(pdq_q1);

    return 0;
}
