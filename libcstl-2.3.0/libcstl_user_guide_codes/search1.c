/*
 * search1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    deque_t* pdeq_coll = create_deque(int);
    list_t* plist_subcoll = create_list(int);
    iterator_t it_pos;
    int i = 0;

    if(pdeq_coll == NULL || plist_subcoll == NULL)
    {
        return -1;
    }

    deque_init(pdeq_coll);
    list_init(plist_subcoll);

    for(i = 1; i <= 7; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(i = 1; i <= 7; ++i)
    {
        deque_push_back(pdeq_coll, i);
    }
    for(i = 3; i <= 6; ++i)
    {
        list_push_back(plist_subcoll, i);
    }

    for(it_pos = deque_begin(pdeq_coll);
        !iterator_equal(it_pos, deque_end(pdeq_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    for(it_pos = list_begin(plist_subcoll);
        !iterator_equal(it_pos, list_end(plist_subcoll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_pos = algo_search(deque_begin(pdeq_coll), deque_end(pdeq_coll),
        list_begin(plist_subcoll), list_end(plist_subcoll));
    while(!iterator_equal(it_pos, deque_end(pdeq_coll)))
    {
        printf("subcoll found starting with element %d\n",
            iterator_distance(deque_begin(pdeq_coll), it_pos) + 1);

        it_pos = algo_search(iterator_next(it_pos), deque_end(pdeq_coll),
            list_begin(plist_subcoll), list_end(plist_subcoll));
    }

    deque_destroy(pdeq_coll);
    list_destroy(plist_subcoll);

    return 0;
}
