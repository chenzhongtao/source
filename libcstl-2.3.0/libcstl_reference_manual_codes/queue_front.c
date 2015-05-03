/*
 * queue_front.c
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

    printf("The element at the front of queue q1 is %d.\n", *(int*)queue_front(pq_q1));

    *(int*)queue_front(pq_q1) -= 5;

    printf("The element at the front of queue q1 is now %d.\n", *(int*)queue_front(pq_q1));

    queue_destroy(pq_q1);

    return 0;
}
