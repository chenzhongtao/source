/*
 * unique2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

static void _difference_one(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output =
        *(int*)cpv_first + 1 == *(int*)cpv_second ||
        *(int*)cpv_first - 1 == *(int*)cpv_second ?
        true : false;
}

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll1 = create_deque(int);
    deque_t* pdeq_coll2 = create_deque(int);
    deque_t* pdeq_coll3 = create_deque(int);
    deque_t* pdeq_coll4 = create_deque(int);
    iterator_t it_pos;
    iterator_t it_end;
    int i = 0;

    if(pdeq_coll1 == NULL || pdeq_coll2 == NULL ||
       pdeq_coll3 == NULL || pdeq_coll4 == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll1);
    deque_init(pdeq_coll2);
    deque_init(pdeq_coll3);
    deque_init(pdeq_coll4);

    deque_push_back(pdeq_coll1, 1);
    deque_push_back(pdeq_coll1, 4);
    deque_push_back(pdeq_coll1, 4);
    deque_push_back(pdeq_coll1, 6);
    deque_push_back(pdeq_coll1, 1);
    deque_push_back(pdeq_coll1, 2);
    deque_push_back(pdeq_coll1, 2);
    deque_push_back(pdeq_coll1, 3);
    deque_push_back(pdeq_coll1, 1);
    deque_push_back(pdeq_coll1, 6);
    deque_push_back(pdeq_coll1, 6);
    deque_push_back(pdeq_coll1, 6);
    deque_push_back(pdeq_coll1, 5);
    deque_push_back(pdeq_coll1, 7);
    deque_push_back(pdeq_coll1, 5);
    deque_push_back(pdeq_coll1, 4);
    deque_push_back(pdeq_coll1, 4);
    deque_assign(pdeq_coll3, pdeq_coll1);
    deque_resize(pdeq_coll2, deque_size(pdeq_coll1));
    deque_resize(pdeq_coll4, deque_size(pdeq_coll1));

    printf("coll1: ");
    for(it_pos = deque_begin(pdeq_coll1);
        !iterator_equal(it_pos, deque_end(pdeq_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_end = algo_unique_copy(deque_begin(pdeq_coll1),
        deque_end(pdeq_coll1), deque_begin(pdeq_coll2));
    printf("coll2: ");
    for(it_pos = deque_begin(pdeq_coll2);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n\n");

    printf("coll3: ");
    for(it_pos = deque_begin(pdeq_coll3);
        !iterator_equal(it_pos, deque_end(pdeq_coll3));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    it_end = algo_unique_copy_if(deque_begin(pdeq_coll3), deque_end(pdeq_coll3),
        deque_begin(pdeq_coll4), _difference_one);
    printf("coll4: ");
    for(it_pos = deque_begin(pdeq_coll4);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    deque_destroy(pdeq_coll1);
    deque_destroy(pdeq_coll2);
    deque_destroy(pdeq_coll3);
    deque_destroy(pdeq_coll4);

    return 0;
}
