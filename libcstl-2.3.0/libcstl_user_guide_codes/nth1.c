/*
 * nth1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll = create_deque(int);
    iterator_t it_pos;
    int i = 0;

    if(pdeq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);

    for(i = 3; i <= 7; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(i = 2; i <= 6; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(i = 1; i <= 5; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    printf("coll: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_nth_element(deque_begin(pdeq_coll),
        iterator_next_n(deque_begin(pdeq_coll), 3), deque_end(pdeq_coll));
    printf("the four last elements are: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, iterator_next_n(deque_begin(pdeq_coll), 4));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_nth_element(deque_begin(pdeq_coll),
        iterator_prev_n(deque_end(pdeq_coll), 4), deque_end(pdeq_coll));
    printf("the four highest elements are: ");
    for(it_pos = iterator_prev_n(deque_end(pdeq_coll), 4);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_nth_element_if(deque_begin(pdeq_coll),
        iterator_next_n(deque_begin(pdeq_coll), 3),
        deque_end(pdeq_coll), fun_greater_int);
    printf("the four highest elements are: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, iterator_next_n(deque_begin(pdeq_coll), 4));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    deque_destroy(pdeq_coll);

    return 0;
}
