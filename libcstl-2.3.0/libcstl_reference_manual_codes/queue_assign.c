/*
 * queue_assign.c
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
    queue_push(pq_q1, 2);
    queue_push(pq_q1, 3);
    queue_push(pq_q2, 10);
    queue_push(pq_q2, 20);

    printf("The length of queue q1 is %d.\n", queue_size(pq_q1));

    queue_assign(pq_q1, pq_q2);

    printf("After assigning, the length of queue q1 is %d.\n", queue_size(pq_q1));

    queue_destroy(pq_q1);
    queue_destroy(pq_q2);

    return 0;
}
