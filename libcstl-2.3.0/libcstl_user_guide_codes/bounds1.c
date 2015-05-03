/*
 * bounds1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    iterator_t it_pos;
    iterator_t it_lower;
    iterator_t it_upper;
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll, i);
    }
    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll, i);
    }

    list_sort(plist_coll);
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    it_lower = algo_lower_bound(list_begin(plist_coll), list_end(plist_coll), 5);
    it_upper = algo_upper_bound(list_begin(plist_coll), list_end(plist_coll), 5);
    printf("5 could get position %d up to %d without breaking the sorting.\n",
        iterator_distance(list_begin(plist_coll), it_lower) + 1,
        iterator_distance(list_begin(plist_coll), it_upper) + 1);

    list_insert(plist_coll,
        algo_lower_bound(list_begin(plist_coll), list_end(plist_coll), 3),
        3);
    list_insert(plist_coll,
        algo_upper_bound(list_begin(plist_coll), list_end(plist_coll), 7),
        7);

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
