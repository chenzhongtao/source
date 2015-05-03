/*
 * psort1.c
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

    algo_partial_sort(deque_begin(pdeq_coll),
        iterator_next_n(deque_begin(pdeq_coll), 5), deque_end(pdeq_coll));
    printf("coll: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_partial_sort_if(deque_begin(pdeq_coll),
        iterator_next_n(deque_begin(pdeq_coll), 5),
        deque_end(pdeq_coll), fun_greater_int);
    printf("coll: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    deque_destroy(pdeq_coll);

    return 0;
}
