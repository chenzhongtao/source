/*
 * adjdiff.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cdeque.h>
#include <cstl/clist.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll1 = create_deque(int);
    list_t* plist_coll2 = create_list(int);
    iterator_t it_pos;

    if(pdeq_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    deque_init_n(pdeq_coll1, 6);
    list_init_n(plist_coll2, deque_size(pdeq_coll1));

    algo_iota(deque_begin(pdeq_coll1), deque_end(pdeq_coll1), 1);
    for(it_pos = deque_begin(pdeq_coll1);
        !iterator_equal(it_pos, deque_end(pdeq_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_adjacent_difference(deque_begin(pdeq_coll1),
        deque_end(pdeq_coll1), list_begin(plist_coll2));
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_adjacent_difference_if(deque_begin(pdeq_coll1), deque_end(pdeq_coll1),
        list_begin(plist_coll2), fun_plus_int);
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_adjacent_difference_if(deque_begin(pdeq_coll1), deque_end(pdeq_coll1),
        list_begin(plist_coll2), fun_multiplies_int);
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    deque_destroy(pdeq_coll1);
    list_destroy(plist_coll2);

    return 0;
}
