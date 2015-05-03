/*
 * deque_size.c
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
    printf("The deque length is %d\n", deque_size(pdq_q1));

    deque_push_back(pdq_q1, 2);
    printf("The deque length is now %d\n", deque_size(pdq_q1));

    deque_destroy(pdq_q1);

    return 0;
}
