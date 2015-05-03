/*
 * stack_init.c
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
    printf("The size fo stack sk1 is %d.\n", stack_size(psk_sk1));

    stack_push(psk_sk1, 10);
    stack_push(psk_sk1, 20);
    stack_push(psk_sk1, 40);
    printf("The size of stack sk1 is now %d.\n", stack_size(psk_sk1));

    stack_init_copy(psk_sk2, psk_sk1);
    printf("The size of stack sk2 is %d.\n", stack_size(psk_sk2));

    stack_destroy(psk_sk1);
    stack_destroy(psk_sk2);

    return 0;
}
