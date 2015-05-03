/*
 * queue_equal.c
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
    queue_push(pq_q2, 2);
    queue_push(pq_q3, 1);

    if(queue_equal(pq_q1, pq_q2))
    {
        printf("The queues q1 and q2 are equal.\n");
    }
    else
    {
        printf("The queues q1 and q2 are not equal.\n");
    }

    if(queue_equal(pq_q1, pq_q3))
    {
        printf("The queues q1 and q3 are equal.\n");
    }
    else
    {
        printf("The queues q1 and q3 are not equal.\n");
    }

    queue_destroy(pq_q1);
    queue_destroy(pq_q2);
    queue_destroy(pq_q3);

    return 0;
}
