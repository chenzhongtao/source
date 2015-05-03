/*
 * queue_pop.c
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

    queue_push(pq_q1, 10);
    queue_push(pq_q1, 20);
    queue_push(pq_q1, 30);

    printf("The queue length is %d.\n", queue_size(pq_q1));
    printf("The element at the front of the queue q1 is %d.\n", *(int*)queue_front(pq_q1));

    queue_pop(pq_q1);

    printf("After a pop, the queue length is %d.\n", queue_size(pq_q1));
    printf("After a pop, the element at the front of the queue q1 is %d.\n", *(int*)queue_front(pq_q1));

    queue_destroy(pq_q1);

    return 0;
}
