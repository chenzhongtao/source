/*
 * stack_top.c
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

    stack_push(psk_sk1, 1);
    stack_push(psk_sk1, 5);

    printf("The top integer of the stack sk1 is %d.\n", *(int*)stack_top(psk_sk1));
    *(int*)stack_top(psk_sk1) -= 1;
    printf("The top integer of the stack sk1 is %d.\n", *(int*)stack_top(psk_sk1));

    stack_destroy(psk_sk1);

    return 0;
}
