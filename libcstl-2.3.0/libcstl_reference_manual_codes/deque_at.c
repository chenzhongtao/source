/*
 * deque_at.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int);
    int* pn_i = NULL;
    int n_j = 0;

    if(pdq_q1 == NULL)
    {
        return -1;
    }

    deque_init(pdq_q1);

    deque_push_back(pdq_q1, 10);
    deque_push_back(pdq_q1, 20);

    pn_i = (int*)deque_at(pdq_q1, 0);
    n_j = *(int*)deque_at(pdq_q1, 1);
    printf("The first element is %d\n", *pn_i);
    printf("The second element is %d\n", n_j);

    deque_destroy(pdq_q1);

    return 0;
}
