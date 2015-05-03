/*
 * minmax2.c
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
    iterator_t it_pos;
    iterator_t it_min;
    iterator_t it_max;
    int i = 0;

    if(pdeq_coll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);

    for(i = 2; i <= 8; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(i = -3; i <= 5; ++i)
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

    it_min = algo_min_element(deque_begin(pdeq_coll), deque_end(pdeq_coll));
    it_max = algo_max_element(deque_begin(pdeq_coll), deque_end(pdeq_coll));
    printf("min: %d\n", *(int*)iterator_get_pointer(it_min));
    printf("max: %d\n", *(int*)iterator_get_pointer(it_max));

    it_min = algo_min_element_if(deque_begin(pdeq_coll),
        deque_end(pdeq_coll), _abs_less);
    it_max = algo_max_element_if(deque_begin(pdeq_coll),
        deque_end(pdeq_coll), _abs_less);
    printf("absolute min: %d\n", *(int*)iterator_get_pointer(it_min));
    printf("absolute max: %d\n", *(int*)iterator_get_pointer(it_max));

    deque_destroy(pdeq_coll);

    return 0;
}
