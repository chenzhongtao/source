/*
 * deque2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

static void _print(const void* cpv_input, void* pv_output)
{
    printf("%s\n", (char*)cpv_input);
}

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll = create_deque(char*);

    if(pdeq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);

    deque_assign_elem(pdeq_coll, 3, "string");
    deque_push_back(pdeq_coll, "last string");
    deque_push_front(pdeq_coll, "first string");

    /* print all elements with new line */
    algo_for_each(deque_begin(pdeq_coll), deque_end(pdeq_coll), _print);
    printf("\n");

    /* remove first and last elements */
    deque_pop_back(pdeq_coll);
    deque_pop_front(pdeq_coll);

    /* print all elements with new line */
    algo_for_each(deque_begin(pdeq_coll), deque_end(pdeq_coll), _print);
    printf("\n");

    /* change size to four elements */
    deque_resize_elem(pdeq_coll, 4, "resized string");

    /* print all elements with new line */
    algo_for_each(deque_begin(pdeq_coll), deque_end(pdeq_coll), _print);
    printf("\n");

    deque_destroy(pdeq_coll);

    return 0;
}
