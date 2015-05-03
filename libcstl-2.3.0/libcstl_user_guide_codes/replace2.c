/*
 * replace2.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _less_5(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input < 5 ? true : false;
}

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    list_t* plist_coll2 = create_list(int);
    iterator_t it_pos;
    int i = 0;

    if(plist_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    list_init(plist_coll2);

    for(i = 2; i <= 7; ++i)
    {
        list_push_back(plist_coll1, i);
    }
    for(i = 4; i <= 9; ++i)
    {
        list_push_back(plist_coll1, i);
    }

    printf("coll1: ");
    for(it_pos = list_begin(plist_coll1);
        !iterator_equal(it_pos, list_end(plist_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_resize(plist_coll2, list_size(plist_coll1));
    /* replace all elements of coll1 from value 6 to value 42 and copy to coll2*/
    algo_replace_copy(list_begin(plist_coll1), list_end(plist_coll1),
        list_begin(plist_coll2), 6, 42);
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* 
     * replace all elemens of coll1 from value less than 5 to value 0 
     * and copy to coll2
     */
    algo_replace_copy_if(list_begin(plist_coll1), list_end(plist_coll1),
        list_begin(plist_coll2), _less_5, 0);
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll1);
    list_destroy(plist_coll2);

    return 0;
}
