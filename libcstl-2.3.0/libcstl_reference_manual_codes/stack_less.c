/*
 * stack_less.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstack.h>

int main(int argc, char* argv[])
{
    stack_t* psk_sk1 = create_stack(int);
    stack_t* psk_sk2 = create_stack(int);
    stack_t* psk_sk3 = create_stack(int);
    size_t t_count = 0;
    int i = 0;

    if(psk_sk1 == NULL || psk_sk2 == NULL || psk_sk3 == NULL)
    {
        return -1;
    }

    stack_init(psk_sk1);
    stack_init(psk_sk2);
    stack_init(psk_sk3);

    stack_push(psk_sk1, 2);
    stack_push(psk_sk1, 4);
    stack_push(psk_sk1, 6);
    stack_push(psk_sk1, 8);
    stack_push(psk_sk2, 5);
    stack_push(psk_sk2, 10);
    stack_push(psk_sk3, 2);
    stack_push(psk_sk3, 4);
    stack_push(psk_sk3, 6);
    stack_push(psk_sk3, 8);

    if(stack_less(psk_sk1, psk_sk2))
    {
        printf("The stack sk1 is less than the stack s2.\n");
    }
    else
    {
        printf("The stack sk1 is not less than the stack s2.\n");
    }

    if(stack_less(psk_sk1, psk_sk3))
    {
        printf("The stack sk1 is less than the stack s3.\n");
    }
    else
    {
        printf("The stack sk1 is not less than the stack s3.\n");
    }

    /* to print out the stack sk1 (by unstacking the elements) */
    printf("The stack sk1 from the top down is: ( ");
    t_count = stack_size(psk_sk1);
    for(i = 0; i < t_count; ++i)
    {
        printf("%d ", *(int*)stack_top(psk_sk1));
        stack_pop(psk_sk1);
    }
    printf(").\n");

    stack_destroy(psk_sk1);
    stack_destroy(psk_sk2);
    stack_destroy(psk_sk3);

    return 0;
}
