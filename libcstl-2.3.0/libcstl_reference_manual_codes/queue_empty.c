/*
 * queue_empty.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>

int main(int argc, char* argv[])
{
    queue_t* pq_q1 = create_queue(int);
    queue_t* pq_q2 = create_queue(int);

    if(pq_q1 == NULL || pq_q2 == NULL)
    {
        return -1;
    }

    queue_init(pq_q1);
    queue_init(pq_q2);

    queue_push(pq_q1, 1);

    if(queue_empty(pq_q1))
    {
        printf("The queue q1 is empty.\n");
    }
    else
    {
        printf("The queue q1 is not empty.\n");
    }

    if(queue_empty(pq_q2))
    {
        printf("The queue q2 is empty.\n");
    }
    else
    {
        printf("The queue q2 is not empty.\n");
    }

    queue_destroy(pq_q1);
    queue_destroy(pq_q2);

    return 0;
}
