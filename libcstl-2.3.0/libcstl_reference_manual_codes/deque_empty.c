/*
 * deque_empty.c
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

    deque_push_back(pdq_q1, 10);
    if(deque_empty(pdq_q1))
    {
        printf("The deque is emtpy.\n");
    }
    else
    {
        printf("The deque is not empty.\n");
    }

    deque_destroy(pdq_q1);

    return 0;
}
