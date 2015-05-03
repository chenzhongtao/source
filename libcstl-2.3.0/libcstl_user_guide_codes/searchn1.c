/*
 * searchn1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll = create_deque(int);
    deque_iterator_t it_pos;
    int i = 0;

    if(pdeq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);

    for(i = 1; i <= 9; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_pos = algo_search_n(deque_begin(pdeq_coll), deque_end(pdeq_coll), 4, 3);
    if(iterator_equal(it_pos, deque_end(pdeq_coll)))
    {
        printf("no four consecutive elements with value 3 found.\n");
    }
    else
    {
        printf("four consecutive elements with value 3 start with %d\n",
            iterator_distance(deque_begin(pdeq_coll), it_pos) + 1);
    }

    it_pos = algo_search_n_if(deque_begin(pdeq_coll),
        deque_end(pdeq_coll), 4, 3, fun_greater_int);
    if(iterator_equal(it_pos, deque_end(pdeq_coll)))
    {
        printf("no four consecutive elements with value > 3 found.\n");
    }
    else
    {
        printf("four consecutive elements with value > 3 start with %d\n",
            iterator_distance(deque_begin(pdeq_coll), it_pos) + 1);
    }

    deque_destroy(pdeq_coll);

    return 0;
}
