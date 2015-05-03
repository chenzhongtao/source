/*
 * deque_max_size.c
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

    printf("The maxmum possible length of the deque is %d\n", deque_max_size(pdq_q1));

    deque_destroy(pdq_q1);

    return 0;
}
