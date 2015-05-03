/*
 * double1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll1 = create_list(double);
    list_t* plist_coll2 = create_list(double);
    iterator_t it_pos;
    double d_data = 0.0;

    if(plist_coll1 == NULL || plist_coll2 == NULL)
    {
        return -1;
    }

    list_init(plist_coll1);
    list_init(plist_coll2);

    list_push_back(plist_coll1, 1);
    list_push_back(plist_coll1, 3);
    list_push_back(plist_coll1, 5);
    list_push_back(plist_coll1, 7);

    d_data = 1;
    list_push_back(plist_coll2, d_data);
    list_push_back(plist_coll2, 3.0);
    list_push_back(plist_coll2, 5e0);
    list_push_back(plist_coll2, (double)7);

    for(it_pos = list_begin(plist_coll1);
        !iterator_equal(it_pos, list_end(plist_coll1));
        it_pos = iterator_next(it_pos))
    {
        printf("%lf ", *(double*)iterator_get_pointer(it_pos));
    }
    printf("\n");
    for(it_pos = list_begin(plist_coll2);
        !iterator_equal(it_pos, list_end(plist_coll2));
        it_pos = iterator_next(it_pos))
    {
        printf("%lf ", *(double*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    list_destroy(plist_coll1);
    list_destroy(plist_coll2);

    return 0;
}
