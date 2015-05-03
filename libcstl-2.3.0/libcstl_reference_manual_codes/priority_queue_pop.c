/*
 * priority_queue_pop.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>

int main(int argc, char* argv[])
{
    priority_queue_t* ppq_pq1 = create_priority_queue(int);

    if(ppq_pq1 == NULL)
    {
        return -1;
    }

    priority_queue_init(ppq_pq1);

    priority_queue_push(ppq_pq1, 10);
    priority_queue_push(ppq_pq1, 20);
    priority_queue_push(ppq_pq1, 30);

    printf("The priority_queue length is %d.\n",
        priority_queue_size(ppq_pq1));
    printf("The element at the top of the priority_queue is %d.\n",
        *(int*)priority_queue_top(ppq_pq1));

    priority_queue_pop(ppq_pq1);

    printf("After a pop, the priority_queue length is %d.\n",
        priority_queue_size(ppq_pq1));
    printf("After a pop, the element at the top of the priority_queue is %d.\n",
        *(int*)priority_queue_top(ppq_pq1));

    priority_queue_destroy(ppq_pq1);

    return 0;
}
