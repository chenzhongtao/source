/*
 * queue_size.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>

int main(int argc, char* argv[])
{
    queue_t* pq_q1 = create_queue(int);

    if(pq_q1 == NULL)
    {
        return -1;
    }

    queue_init(pq_q1);

    queue_push(pq_q1, 1);
    printf("The queue length is %d.\n", queue_size(pq_q1));

    queue_push(pq_q1, 2);
    printf("The queue length is now %d.\n", queue_size(pq_q1));

    queue_destroy(pq_q1);

    return 0;
}
