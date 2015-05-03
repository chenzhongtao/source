/*
 * deque_begin.c
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

    deque_push_back(pdq_q1, 1);
    deque_push_back(pdq_q1, 2);

    it_q = deque_begin(pdq_q1);
    printf("The first element of q1 is %d\n", *(int*)iterator_get_pointer(it_q));

    *(int*)iterator_get_pointer(it_q) = 20;
    printf("The first element of q1 is now %d\n", *(int*)iterator_get_pointer(it_q));

    deque_destroy(pdq_q1);

    return 0;
}
