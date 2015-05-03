/*
 * pqueue1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>

int main(int argc, char* argv[])
{
    priority_queue_t* ppque_coll = create_priority_queue(double);

    if(ppque_coll == NULL)
    {
        return -1;
    }

    priority_queue_init(ppque_coll);

    priority_queue_push(ppque_coll, 66.6);
    priority_queue_push(ppque_coll, 22.2);
    priority_queue_push(ppque_coll, 44.4);

    printf("%lf ", *(double*)priority_queue_top(ppque_coll));
    priority_queue_pop(ppque_coll);
    printf("%lf\n", *(double*)priority_queue_top(ppque_coll));
    priority_queue_pop(ppque_coll);

    priority_queue_push(ppque_coll, 11.1);
    priority_queue_push(ppque_coll, 55.5);
    priority_queue_push(ppque_coll, 33.3);

    priority_queue_pop(ppque_coll);

    while(!priority_queue_empty(ppque_coll))
    {
        printf("%lf ", *(double*)priority_queue_top(ppque_coll));
        priority_queue_pop(ppque_coll);
    }
    printf("\n");

    priority_queue_destroy(ppque_coll);

    return 0;
}
