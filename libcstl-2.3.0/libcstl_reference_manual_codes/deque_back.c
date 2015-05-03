/*
 * deque_back.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    deque_t* pdq_q1 = create_deque(int);
    int* pn_i = NULL;
    int* pn_j = NULL;

    if(pdq_q1 == NULL)
    {
        return -1;
    }

    deque_init(pdq_q1);

    deque_push_back(pdq_q1, 10);
    deque_push_back(pdq_q1, 11);

    pn_i = (int*)deque_back(pdq_q1);
    pn_j = (int*)deque_back(pdq_q1);
    printf("The last integer of q1 is %d\n", *pn_i);
    (*pn_i)++;
    printf("The modified last integer of q1 is %d\n", *pn_j);

    deque_destroy(pdq_q1);

    return 0;
}
