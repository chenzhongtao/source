/*
 * copy4.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/cdeque.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll1 = create_vector(int);
    list_t* plist_coll2 = create_list(int);
    deque_t* pdeq_coll3 = create_deque(int);
    deque_t* pdeq_coll4 = create_deque(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_coll1 == NULL || plist_coll2 == NULL ||
       pdeq_coll3 == NULL || pdeq_coll4 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    list_init(plist_coll2);
    deque_init(pdeq_coll3);
    deque_init(pdeq_coll4);

    for(i = 0; i <= 8; ++i)
    {
        vector_push_back(pvec_coll1, i);
        list_push_back(plist_coll2, i);
    }
    deque_resize(pdeq_coll3, vector_size(pvec_coll1));
    deque_resize(pdeq_coll4, vector_size(pvec_coll1));

    algo_copy(vector_begin(pvec_coll1), vector_end(pvec_coll1),
        deque_begin(pdeq_coll3));
    algo_copy_backward(list_begin(plist_coll2), list_end(plist_coll2),
        deque_end(pdeq_coll4));

    printf("coll1: ");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll3: ");
    for(it_pos = deque_begin(pdeq_coll3);
        !iterator_equal(it_pos, deque_end(pdeq_coll3));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll4: ");
    for(it_pos = deque_begin(pdeq_coll4);
        !iterator_equal(it_pos, deque_end(pdeq_coll4));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_copy(iterator_advance(vector_begin(pvec_coll1), 2),
        iterator_advance(vector_begin(pvec_coll1), 7),
        vector_begin(pvec_coll1));
    algo_copy(iterator_advance(list_begin(plist_coll2), 2),
        iterator_advance(list_begin(plist_coll2), 7),
        iterator_advance(list_begin(plist_coll2), 4));
    algo_copy_backward(iterator_advance(deque_begin(pdeq_coll3), 2),
        iterator_advance(deque_begin(pdeq_coll3), 7),
        iterator_advance(deque_begin(pdeq_coll3), 5));
    algo_copy_backward(iterator_advance(deque_begin(pdeq_coll4), 2),
        iterator_advance(deque_begin(pdeq_coll4), 7),
        deque_end(pdeq_coll4));

    printf("\n");
    printf("coll1: ");
    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll3: ");
    for(it_pos = deque_begin(pdeq_coll3);
        !iterator_equal(it_pos, deque_end(pdeq_coll3));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll4: ");
    for(it_pos = deque_begin(pdeq_coll4);
        !iterator_equal(it_pos, deque_end(pdeq_coll4));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_coll1);
    list_destroy(plist_coll2);
    deque_destroy(pdeq_coll3);
    deque_destroy(pdeq_coll4);

    return 0;
}
