/*
 * merge1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cset.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    set_t* pset_coll2 = create_set(int);
    vector_t* pvec_merge = create_vector(int);
    iterator_t it_pos;
    int i = 0;

    if(plist_coll1 == NULL || pset_coll2 == NULL || pvec_merge == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    set_init(pset_coll2);
    vector_init(pvec_merge);

    for(i = 1; i <= 6; ++i)
    {
        list_push_back(plist_coll1, i);
    }
    for(i = 3; i <= 8; ++i)
    {
        set_insert(pset_coll2, i);
    }
    vector_resize(pvec_merge, list_size(plist_coll1) + set_size(pset_coll2));

    printf("coll1: ");
    for(it_pos = list_begin(plist_coll1);
        !iterator_equal(it_pos, list_end(plist_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll2: ");
    for(it_pos = set_begin(pset_coll2);
        !iterator_equal(it_pos, set_end(pset_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_merge(list_begin(plist_coll1), list_end(plist_coll1),
        set_begin(pset_coll2), set_end(pset_coll2), vector_begin(pvec_merge));
    printf("merge: ");
    for(it_pos = vector_begin(pvec_merge);
        !iterator_equal(it_pos, vector_end(pvec_merge));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll1);
    set_destroy(pset_coll2);
    vector_destroy(pvec_merge);

    return 0;
}
