/*
 * stack1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cstack.h>

int main(int argc, char* argv[])
{
    stack_t* pstk_coll = create_stack(int);

    if(pstk_coll == NULL)
    {
        return -1;
    }

    stack_init(pstk_coll);

    stack_push(pstk_coll, 1);
    stack_push(pstk_coll, 2);
    stack_push(pstk_coll, 3);

    printf("%d ", *(int*)stack_top(pstk_coll));
    stack_pop(pstk_coll);
    printf("%d ", *(int*)stack_top(pstk_coll));
    stack_pop(pstk_coll);

    *(int*)stack_top(pstk_coll) = 77;
    stack_push(pstk_coll, 4);
    stack_push(pstk_coll, 5);
    stack_pop(pstk_coll);

    while(!stack_empty(pstk_coll))
    {
        printf("%d ", *(int*)stack_top(pstk_coll));
        stack_pop(pstk_coll);
    }
    printf("\n");

    stack_destroy(pstk_coll);

    return 0;
}
