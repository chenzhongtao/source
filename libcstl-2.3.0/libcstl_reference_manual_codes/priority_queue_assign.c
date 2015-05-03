/*
 * priority_queue_assign.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>

int main(int argc, char* argv[])
{
    priority_queue_t* ppq_pq1 = create_priority_queue(int);
    priority_queue_t* ppq_pq2 = create_priority_queue(int);

    if(ppq_pq1 == NULL || ppq_pq2 == NULL)
    {
        return -1;
    }

    priority_queue_init(ppq_pq1);
    priority_queue_init(ppq_pq2);

    priority_queue_push(ppq_pq1, 1);
    priority_queue_push(ppq_pq1, 2);
    priority_queue_push(ppq_pq1, 3);
    priority_queue_push(ppq_pq2, 10);
    priority_queue_push(ppq_pq2, 20);

    printf("The length of priority_queue pq1 is %d.\n",
        priority_queue_size(ppq_pq1));

    priority_queue_assign(ppq_pq1, ppq_pq2);

    printf("After assignment, the length of priority_queue pq1 is %d.\n",
        priority_queue_size(ppq_pq1));

    priority_queue_destroy(ppq_pq1);
    priority_queue_destroy(ppq_pq2);

    return 0;
}
