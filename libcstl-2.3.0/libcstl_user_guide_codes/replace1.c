/*
 * replace1.c
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
    list_t* plist_coll = create_list(int);
    iterator_t it_pos;
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    for(i = 2; i <= 7; ++i)
    {
        list_push_back(plist_coll, i);
    }
    for(i = 4; i <= 9; ++i)
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

    /* replace all elements from value 6 to value 42 */
    algo_replace(list_begin(plist_coll), list_end(plist_coll), 6, 42);
    printf("coll: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* replace all elemens from value less than 5 to value 0 */
    algo_replace_if(list_begin(plist_coll), list_end(plist_coll), _less_5, 0);
    printf("coll: ");
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
