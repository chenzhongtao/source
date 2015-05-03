/*
 * remove5.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _less_4(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input < 4 ? true : false;
}

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    iterator_t it_pos;
    iterator_t it_end;
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    for(i = 2; i <= 6; ++i)
    {
        list_push_back(plist_coll, i);
    }
    for(i = 4; i <= 9; ++i)
    {
        list_push_back(plist_coll, i);
    }
    for(i = 1; i <= 7; ++i)
    {
        list_push_back(plist_coll, i);
    }

    printf("coll: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* 
     * remove all elements with value 5
     */
    it_end = algo_remove(list_begin(plist_coll), list_end(plist_coll), 5);

    printf("size not changed: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* erase the "removed" elements in the container */
    list_erase_range(plist_coll, it_end, list_end(plist_coll));
    printf("size changed: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /*
     * remove all elements with value less than 4
     */
    list_erase_range(plist_coll,
        algo_remove_if(list_begin(plist_coll), list_end(plist_coll), _less_4),
        list_end(plist_coll));
    printf("< 4 removed: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll);

    return 0;
}
