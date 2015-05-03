/*
 * setalgos.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    deque_t* pdeq_coll2 = create_deque(int);
    vector_t* pvec_result = create_vector(int);
    iterator_t it_pos;
    iterator_t it_end;
    int i = 0;

    if(plist_coll1 == NULL || pdeq_coll2 == NULL || pvec_result == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    deque_init(pdeq_coll2);
    vector_init(pvec_result);

    list_push_back(plist_coll1, 1);
    list_push_back(plist_coll1, 2);
    list_push_back(plist_coll1, 2);
    list_push_back(plist_coll1, 4);
    list_push_back(plist_coll1, 6);
    list_push_back(plist_coll1, 7);
    list_push_back(plist_coll1, 7);
    list_push_back(plist_coll1, 9);
    deque_push_back(pdeq_coll2, 2);
    deque_push_back(pdeq_coll2, 2);
    deque_push_back(pdeq_coll2, 2);
    deque_push_back(pdeq_coll2, 3);
    deque_push_back(pdeq_coll2, 6);
    deque_push_back(pdeq_coll2, 6);
    deque_push_back(pdeq_coll2, 8);
    deque_push_back(pdeq_coll2, 9);
    vector_resize(pvec_result, list_size(plist_coll1) + deque_size(pdeq_coll2));

    printf("coll1: ");
    for(it_pos = list_begin(plist_coll1);
        !iterator_equal(it_pos, list_end(plist_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll2: ");
    for(it_pos = deque_begin(pdeq_coll2);
        !iterator_equal(it_pos, deque_end(pdeq_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_end = algo_merge(list_begin(plist_coll1), list_end(plist_coll1), 
        deque_begin(pdeq_coll2), deque_end(pdeq_coll2), vector_begin(pvec_result));
    printf("merge: ");
    for(it_pos = vector_begin(pvec_result);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    it_end = algo_set_union(list_begin(plist_coll1), list_end(plist_coll1), 
        deque_begin(pdeq_coll2), deque_end(pdeq_coll2), vector_begin(pvec_result));
    printf("union: ");
    for(it_pos = vector_begin(pvec_result);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    it_end = algo_set_intersection(list_begin(plist_coll1), list_end(plist_coll1), 
        deque_begin(pdeq_coll2), deque_end(pdeq_coll2), vector_begin(pvec_result));
    printf("intersection: ");
    for(it_pos = vector_begin(pvec_result);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    it_end = algo_set_difference(list_begin(plist_coll1), list_end(plist_coll1), 
        deque_begin(pdeq_coll2), deque_end(pdeq_coll2), vector_begin(pvec_result));
    printf("difference: ");
    for(it_pos = vector_begin(pvec_result);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    it_end = algo_set_symmetric_difference(list_begin(plist_coll1), list_end(plist_coll1), 
        deque_begin(pdeq_coll2), deque_end(pdeq_coll2), vector_begin(pvec_result));
    printf("symmetric difference: ");
    for(it_pos = vector_begin(pvec_result);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll1);
    deque_destroy(pdeq_coll2);
    vector_destroy(pvec_result);

    return 0;
}
