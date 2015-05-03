/*
 * swap2.c
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
    iterator_t it_pos;
    iterator_t it_end;
    int i = 0;

    if(pvec_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    vector_init(pvec_coll1);
    list_init(plist_coll2);

    for(i = 1; i <= 9; ++i)
    {
        vector_push_back(pvec_coll1, i);
    }
    for(i = 11; i <= 23; ++i)
    {
        list_push_back(plist_coll2, i);
    }

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
    printf("\n\n");

    it_end = algo_swap_ranges(vector_begin(pvec_coll1),
        vector_end(pvec_coll1), list_begin(plist_coll2));
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
    printf("\n\n");

    if(!iterator_equal(it_end, list_end(plist_coll2)))
    {
        printf("first element not modified: %d\n",
            *(int*)iterator_get_pointer(it_end));
    }

    vector_destroy(pvec_coll1);
    list_destroy(plist_coll2);

    return 0;
}
