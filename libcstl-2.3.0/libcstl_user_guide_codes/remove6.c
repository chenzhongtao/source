/*
 * remove6.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _greater_4(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 4 ? true : false;
}

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(int);
    list_t* plist_coll2 = create_list(int);
    iterator_t it_pos;
    iterator_t it_end;
    int i = 0;

    if(plist_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    list_init(plist_coll2);

    for(i = 1; i <= 6; ++i)
    {
        list_push_back(plist_coll1, i);
    }
    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll1, i);
    }

    list_resize(plist_coll2, list_size(plist_coll1));

    printf("coll1: ");
    for(it_pos = list_begin(plist_coll1);
        !iterator_equal(it_pos, list_end(plist_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* remove elements that with value 3 */
    it_end = algo_remove_copy(list_begin(plist_coll1), list_end(plist_coll1),
        list_begin(plist_coll2), 3);
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* remove elements that with value greater than 4 */
    it_end = algo_remove_copy_if(list_begin(plist_coll1), list_end(plist_coll1),
        list_begin(plist_coll2), _greater_4);
    printf("coll2: ");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, it_end);
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll1);
    list_destroy(plist_coll2);

    return 0;
}
