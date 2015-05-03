/*
 * fun_logical_and.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

static void _print_bool(const void* cpv_input, void* pv_output)
{
    if(*(bool_t*)cpv_input)
    {
        printf("true ");
    }
    else
    {
        printf("false ");
    }
}

int main(int argc, char* argv[])
{
    deque_t* pdeq_d1 = create_deque(bool_t);
    deque_t* pdeq_d2 = create_deque(bool_t);
    deque_t* pdeq_d3 = create_deque(bool_t);
    int i = 0;

    if(pdeq_d1 == NULL || pdeq_d2 == NULL || pdeq_d3 == NULL)
    {
        return -1;
    }

    deque_init(pdeq_d1);
    deque_init(pdeq_d2);
    deque_init_n(pdeq_d3, 7);

    for(i = 0; i < 7; ++i)
    {
        deque_push_back(pdeq_d1, (bool_t)(rand() % 2));
        deque_push_back(pdeq_d2, (bool_t)(rand() % 2));
    }

    printf("The original deque d1 = ( ");
    algo_for_each(deque_begin(pdeq_d1), deque_end(pdeq_d1), _print_bool);
    printf(")\n");
    printf("The original deque d2 = ( ");
    algo_for_each(deque_begin(pdeq_d2), deque_end(pdeq_d2), _print_bool);
    printf(")\n");

    algo_transform_binary(deque_begin(pdeq_d1), deque_end(pdeq_d1),
        deque_begin(pdeq_d2), deque_begin(pdeq_d3), fun_logical_and_bool);

    printf("The deque which is the conjuction of d1 & d2 is d3 = ( "); 
    algo_for_each(deque_begin(pdeq_d3), deque_end(pdeq_d3), _print_bool);
    printf(")\n");

    deque_destroy(pdeq_d1);
    deque_destroy(pdeq_d2);
    deque_destroy(pdeq_d3);

    return 0;
}
