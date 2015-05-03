/*
 * includes.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    vector_t* pvec_coll2 = create_vector(int);
    iterator_t it_pos;
    int i = 0;

    if(pvec_coll2 == NULL || plist_coll1 == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    vector_init(pvec_coll2);

    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll1, i);
    }
    vector_push_back(pvec_coll2, 3);
    vector_push_back(pvec_coll2, 4);
    vector_push_back(pvec_coll2, 7);

    printf("coll1: ");
    for(it_pos = list_begin(plist_coll1);
        !iterator_equal(it_pos, list_end(plist_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    printf("coll2: ");
    for(it_pos = vector_begin(pvec_coll2);
        !iterator_equal(it_pos, vector_end(pvec_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    if(algo_includes(list_begin(plist_coll1), list_end(plist_coll1),
        vector_begin(pvec_coll2), vector_end(pvec_coll2)))
    {
        printf("all elements of coll2 are also in coll1\n");
    }
    else
    {
        printf("not all elements of coll2 are also in coll1\n");
    }

    list_destroy(plist_coll1);
    vector_destroy(pvec_coll2);

    return 0;
}
