/*
 * stack_empty.c
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

    if(stack_empty(psk_sk1))
    {
        printf("The stack sk1 is empty.\n");
    }
    else
    {
        printf("The stack sk1 is not empty.\n");
    }

    if(stack_empty(psk_sk2))
    {
        printf("The stack sk2 is empty.\n");
    }
    else
    {
        printf("The stack sk2 is not empty.\n");
    }

    stack_destroy(psk_sk1);
    stack_destroy(psk_sk2);

    return 0;
}
