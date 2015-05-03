/*
 * copy2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cdeque.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    vector_t* pvec_coll2 = create_vector(int);
    deque_t* pdeq_coll3 = create_deque(int);
    int i = 0;

    if(plist_coll1 == NULL || pvec_coll2 == NULL || pdeq_coll3 == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    vector_init(pvec_coll2);

    /* insert elements from 1 to 9 */
    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll1, i);
    }

    /*
     * resize distination to have enough room for
     * the overwrite algorithm
     */
    vector_resize(pvec_coll2, list_size(plist_coll1));

    /* copy elements from first to second collection */
    algo_copy(list_begin(plist_coll1), list_end(plist_coll1), vector_begin(pvec_coll2));

    /* initialize third collection with enough room */
    deque_init_n(pdeq_coll3, list_size(plist_coll1));

    /* copy elements from first to third collection */
    algo_copy(list_begin(plist_coll1), list_end(plist_coll1), deque_begin(pdeq_coll3));

    list_destroy(plist_coll1);
    vector_destroy(pvec_coll2);
    deque_destroy(pdeq_coll3);

    return 0;
}
