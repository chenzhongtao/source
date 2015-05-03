/*
 * fill1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(char*);
    iterator_t it_pos;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init_n(plist_coll, 10);

    algo_fill(list_begin(plist_coll), list_end(plist_coll), "hello");
    printf("coll: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%s ", (char*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_fill_n(list_begin(plist_coll), list_size(plist_coll) - 2, "again");
    printf("coll: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%s ", (char*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_fill(iterator_next(list_begin(plist_coll)),
        iterator_prev(list_end(plist_coll)), "mmmm");
    printf("coll: ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%s ", (char*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll);

    return 0;
}
