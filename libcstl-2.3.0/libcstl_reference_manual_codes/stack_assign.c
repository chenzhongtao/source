/*
 * stack_assign.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstack.h>

int main(int argc, char* argv[])
{
    stack_t* psk_sk1 = create_stack(int);
    stack_t* psk_sk2 = create_stack(int);

    if(psk_sk1 == NULL || psk_sk2 == NULL)
    {
        return -1;
    }

    stack_init(psk_sk1);
    stack_init(psk_sk2);

    stack_push(psk_sk1, 1);
    stack_push(psk_sk1, 2);
    stack_push(psk_sk2, 10);
    stack_push(psk_sk2, 20);
    stack_push(psk_sk2, 30);

    printf("The size of stack sk1 is %d and the top element is %d.\n",
        stack_size(psk_sk1), *(int*)stack_top(psk_sk1));

    stack_assign(psk_sk1, psk_sk2);

    printf("After assigning the size of stack sk1 is %d and the top element is %d.\n",
        stack_size(psk_sk1), *(int*)stack_top(psk_sk1));

    stack_destroy(psk_sk1);
    stack_destroy(psk_sk2);

    return 0;
}
