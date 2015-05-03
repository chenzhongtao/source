/*
 * queue_init.c
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

    /* Create an empty queue */
    queue_init(pq_q1);

    printf("The length of queue q1 is %d.\n", queue_size(pq_q1));
    /* Then push 3 elements */
    queue_push(pq_q1, 1);
    queue_push(pq_q1, 2);
    queue_push(pq_q1, 3);

    /* Create an copy queue q2 with q1 */
    queue_init_copy(pq_q2, pq_q1);
    printf("The length of queue q2 is %d.\n", queue_size(pq_q2));

    queue_destroy(pq_q1);
    queue_destroy(pq_q2);

    return 0;
}
