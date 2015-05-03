/*
 * copy3.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    vector_t* pvec_coll1 = create_vector(int);
    list_t* plist_coll2 = create_list(int);
    list_t* plist_coll3 = create_list(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_coll1 == NULL || plist_coll2 == NULL || plist_coll3 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    list_init(plist_coll2);
    list_init(plist_coll3);

    for(i = 1; i <= 9; ++i)
    {
        vector_push_back(pvec_coll1, i);
    }

    list_resize(plist_coll2, vector_size(pvec_coll1));
    list_resize(plist_coll3, vector_size(pvec_coll1));

    algo_copy(vector_begin(pvec_coll1), vector_end(pvec_coll1),
        list_begin(plist_coll2));
    algo_copy_n(vector_begin(pvec_coll1), 5, list_begin(plist_coll3));

    for(it_pos = vector_begin(pvec_coll1);
        !iterator_equal(it_pos, vector_end(pvec_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    for(it_pos = list_begin(plist_coll3);
        !iterator_equal(it_pos, list_end(plist_coll3));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    vector_destroy(pvec_coll1);
    list_destroy(plist_coll2);
    list_destroy(plist_coll3);

    return 0;
}
