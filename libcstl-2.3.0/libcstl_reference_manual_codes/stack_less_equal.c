/*
 * stack_less_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstack.h>

int main(int argc, char* argv[])
{
    stack_t* psk_sk1 = create_stack(int);
    stack_t* psk_sk2 = create_stack(int);
    stack_t* psk_sk3 = create_stack(int);

    if(psk_sk1 == NULL || psk_sk2 == NULL || psk_sk3 == NULL)
    {
        return -1;
    }

    stack_init(psk_sk1);
    stack_init(psk_sk2);
    stack_init(psk_sk3);

    stack_push(psk_sk1, 5);
    stack_push(psk_sk1, 10);
    stack_push(psk_sk2, 1);
    stack_push(psk_sk2, 2);
    stack_push(psk_sk3, 5);
    stack_push(psk_sk3, 10);

    if(stack_less_equal(psk_sk1, psk_sk2))
    {
        printf("The stack sk1 is less than or equal to the stack sk2.\n");
    }
    else
    {
        printf("The stack sk1 is greater than the stack sk2.\n");
    }

    if(stack_less_equal(psk_sk1, psk_sk3))
    {
        printf("The stack sk1 is less than or equal to the stack sk3.\n");
    }
    else
    {
        printf("The stack sk1 is greater than the stack sk3.\n");
    }

    stack_destroy(psk_sk1);
    stack_destroy(psk_sk2);
    stack_destroy(psk_sk3);

    return 0;
}