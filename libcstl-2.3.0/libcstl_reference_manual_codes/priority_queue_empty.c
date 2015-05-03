/*
 * priority_queue_empty.c
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
    if(priority_queue_empty(ppq_pq1))
    {
        printf("The priority_queue pq1 is empty.\n");
    }
    else
    {
        printf("The priority_queue pq1 is not empty.\n");
    }

    if(priority_queue_empty(ppq_pq2))
    {
        printf("The priority_queue pq2 is empty.\n");
    }
    else
    {
        printf("The priority_queue pq2 is not empty.\n");
    }

    priority_queue_destroy(ppq_pq1);
    priority_queue_destroy(ppq_pq2);

    return 0;
}
