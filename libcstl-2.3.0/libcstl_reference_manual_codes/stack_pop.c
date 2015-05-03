/*
 * stack_pop.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstack.h>

int main(int argc, char* argv[])
{
    stack_t* psk_sk1 = create_stack(int);

    if(psk_sk1 == NULL)
    {
        return -1;
    }

    stack_init(psk_sk1);

    stack_push(psk_sk1, 10);
    stack_push(psk_sk1, 20);
    stack_push(psk_sk1, 30);

    printf("The stack length is %d.\n", stack_size(psk_sk1));
    printf("The element at the top of the stack is %d.\n", *(int*)stack_top(psk_sk1));

    stack_pop(psk_sk1);

    printf("After a pop, the stack length is %d.\n", stack_size(psk_sk1));
    printf("After a pop, the element at the top of the stack is %d.\n", *(int*)stack_top(psk_sk1));

    stack_destroy(psk_sk1);

    return 0;
}
