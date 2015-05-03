/*
 * unique1.c
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
    iterator_t it_end;
    int i = 0;

    if(pdeq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);

    deque_push_back(pdeq_coll, 1);
    deque_push_back(pdeq_coll, 4);
    deque_push_back(pdeq_coll, 4);
    deque_push_back(pdeq_coll, 6);
    deque_push_back(pdeq_coll, 1);
    deque_push_back(pdeq_coll, 2);
    deque_push_back(pdeq_coll, 2);
    deque_push_back(pdeq_coll, 3);
    deque_push_back(pdeq_coll, 1);
    deque_push_back(pdeq_coll, 6);
    deque_push_back(pdeq_coll, 6);
    deque_push_back(pdeq_coll, 6);
    deque_push_back(pdeq_coll, 5);
    deque_push_back(pdeq_coll, 7);
    deque_push_back(pdeq_coll, 5);
    deque_push_back(pdeq_coll, 4);
    deque_push_back(pdeq_coll, 4);

    printf("coll: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_end = algo_unique(deque_begin(pdeq_coll), deque_end(pdeq_coll));
    printf("coll: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n\n");

    printf("coll: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    it_end = algo_unique_if(deque_begin(pdeq_coll),
        deque_end(pdeq_coll), fun_greater_int);
    printf("coll: ");
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    deque_destroy(pdeq_coll);

    return 0;
}
