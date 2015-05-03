/*
 * queue_greater.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>

int main(int argc, char* argv[])
{
    queue_t* pq_q1 = create_queue(int);
    queue_t* pq_q2 = create_queue(int);
    queue_t* pq_q3 = create_queue(int);

    if(pq_q1 == NULL || pq_q2 == NULL || pq_q3 == NULL)
    {
        return -1;
    }

    queue_init(pq_q1);
    queue_init(pq_q2);
    queue_init(pq_q3);

    queue_push(pq_q1, 1);
    queue_push(pq_q1, 2);
    queue_push(pq_q1, 3);
    queue_push(pq_q2, 5);
    queue_push(pq_q2, 10);
    queue_push(pq_q3, 1);
    queue_push(pq_q3, 2);

    if(queue_greater(pq_q1, pq_q2))
    {
        printf("The queue q1 is greater than the queue q2.\n");
    }
    else
    {
        printf("The queue q1 is not greater than the queue q2.\n");
    }

    if(queue_greater(pq_q1, pq_q3))
    {
        printf("The queue q1 is greater than the queue q3.\n");
    }
    else
    {
        printf("The queue q1 is not greater than the queue q3.\n");
    }

    queue_destroy(pq_q1);
    queue_destroy(pq_q2);
    queue_destroy(pq_q3);

    return 0;
}
