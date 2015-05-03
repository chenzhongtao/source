/*
 * queue1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cqueue.h>

int main(int argc, char* argv[])
{
    queue_t* pque_coll = create_queue(char*);

    if(pque_coll == NULL)
    {
        return -1;
    }

    queue_init(pque_coll);

    queue_push(pque_coll, "There ");
    queue_push(pque_coll, "are ");
    queue_push(pque_coll, "more than ");

    printf("%s ", (char*)queue_front(pque_coll));
    queue_pop(pque_coll);
    printf("%s ", (char*)queue_front(pque_coll));
    queue_pop(pque_coll);

    queue_push(pque_coll, "four ");
    queue_push(pque_coll, "words!");
    queue_pop(pque_coll);

    printf("%s ", (char*)queue_front(pque_coll));
    queue_pop(pque_coll);
    printf("%s ", (char*)queue_front(pque_coll));
    queue_pop(pque_coll);
    printf("\n");

    printf("numbers of elements in the queue : %u\n", queue_size(pque_coll));

    queue_destroy(pque_coll);

    return 0;
}
