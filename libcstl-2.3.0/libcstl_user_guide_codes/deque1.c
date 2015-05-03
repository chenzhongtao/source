/*
 * deque1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>

int main(int argc, char* argv[])
{
    /* deque container for float-point elements */
    deque_t* pdq_coll = create_deque(float);
    int i = 0;

    if(pdq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdq_coll);

    /* insert elements from 1.1 to 6.6 each at the front */
    for(i = 1; i <= 6; ++i)
    {
        /* insert at the front */
        deque_push_front(pdq_coll, i * 1.1);
    }

    /* print all elements followed by a space */
    for(i = 0; i < deque_size(pdq_coll); ++i)
    {
        printf("%f ", *(float*)deque_at(pdq_coll, i));
    }
    printf("\n");

    deque_destroy(pdq_coll);

    return 0;
}
