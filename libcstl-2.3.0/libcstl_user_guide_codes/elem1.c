/*
 * elem1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

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

    for(i = 0; i < 10; ++i)
    {
        list_push_back(plist_coll, i);
    }
    list_push_back(plist_coll, 45);
    list_push_back(plist_coll, 0);
    list_push_back(plist_coll, -34);
    list_push_back(plist_coll, 995);
    list_push_back(plist_coll, 34);
    list_push_back(plist_coll, -2);

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
