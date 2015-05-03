/*
 * stack_not_equal.c
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

    stack_push(psk_sk1, 1);
    stack_push(psk_sk2, 2);
    stack_push(psk_sk3, 1);

    if(stack_not_equal(psk_sk1, psk_sk2))
    {
        printf("The stacks sk1 and sk2 are not equal.\n");
    }
    else
    {
        printf("The stacks sk1 and sk2 are equal.\n");
    }

    if(stack_not_equal(psk_sk1, psk_sk3))
    {
        printf("The stacks sk1 and sk3 are not equal.\n");
    }
    else
    {
        printf("The stacks sk1 and sk3 are equal.\n");
    }

    stack_destroy(psk_sk1);
    stack_destroy(psk_sk2);
    stack_destroy(psk_sk3);

    return 0;
}
