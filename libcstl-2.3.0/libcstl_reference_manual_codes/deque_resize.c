/*
 * deque_resize.c
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
    deque_push_back(pdq_q1, 20);
    deque_push_back(pdq_q1, 30);

    deque_resize_elem(pdq_q1, 4, 40);
    printf("The size of q1 is: %d\n", deque_size(pdq_q1));
    printf("The value of the last element is %d\n", *(int*)deque_back(pdq_q1));

    deque_resize(pdq_q1, 5);
    printf("The size of q1 is now: %d\n", deque_size(pdq_q1));
    printf("The value of the last element is now %d\n", *(int*)deque_back(pdq_q1));

    deque_resize(pdq_q1, 2);
    printf("The reduced size of q1 is: %d\n", deque_size(pdq_q1));
    printf("The value of the last element is now %d\n", *(int*)deque_back(pdq_q1));

    deque_destroy(pdq_q1);

    return 0;
}
