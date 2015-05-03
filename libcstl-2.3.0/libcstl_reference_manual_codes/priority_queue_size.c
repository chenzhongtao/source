/*
 * priority_queue_size.c
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

    priority_queue_push(ppq_pq1, 1);
    printf("The priority_queue length is %d.\n",
        priority_queue_size(ppq_pq1));

    priority_queue_push(ppq_pq1, 2);
    printf("The priority_queue length is now %d.\n",
        priority_queue_size(ppq_pq1));

    priority_queue_destroy(ppq_pq1);

    return 0;
}
