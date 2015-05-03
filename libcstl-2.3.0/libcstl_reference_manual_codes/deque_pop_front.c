/*
 * deque_pop_front.c
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
    deque_push_back(pdq_q1, 2);

    printf("The first element is: %d\n", *(int*)deque_front(pdq_q1));
    printf("The second element is: %d\n", *(int*)deque_back(pdq_q1));

    deque_pop_front(pdq_q1);
    printf("After deleting the element at the beginning of the deque, the first element is: %d\n", *(int*)deque_front(pdq_q1));

    deque_destroy(pdq_q1);

    return 0;
}
