/*
 * minmax1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

static void _abs_less(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ?
        true : false;
}

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll = create_deque(int);
    iterator_t it_first;
    iterator_t it_second;
    iterator_t it_min;
    iterator_t it_max;

    if(pdeq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);

    deque_push_back(pdeq_coll, 3);
    deque_push_back(pdeq_coll, -5);

    it_first = deque_begin(pdeq_coll);
    it_second = iterator_next(deque_begin(pdeq_coll));
    it_min = algo_min(it_first, it_second);
    it_max = algo_max(it_first, it_second);
    printf("min: %d\n", *(int*)iterator_get_pointer(it_min));
    printf("max: %d\n", *(int*)iterator_get_pointer(it_max));

    it_min = algo_min_if(it_first, it_second, _abs_less);
    it_max = algo_max_if(it_first, it_second, _abs_less);
    printf("absolute min: %d\n", *(int*)iterator_get_pointer(it_min));
    printf("absolute max: %d\n", *(int*)iterator_get_pointer(it_max));

    deque_destroy(pdeq_coll);

    return 0;
}
