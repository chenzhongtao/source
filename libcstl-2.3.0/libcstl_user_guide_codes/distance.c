/*
 * distance.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    list_iterator_t it_pos;
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    for(i = -3; i <= 9; ++i)
    {
        list_push_back(plist_coll, i);
    }

    it_pos = algo_find(list_begin(plist_coll), list_end(plist_coll), 5);
    if(iterator_equal(it_pos, list_end(plist_coll)))
    {
        printf("5 not found!\n");
    }
    else
    {
        printf("distance between beginning and 5 : %d\n",
            iterator_distance(list_begin(plist_coll), it_pos));
    }

    list_destroy(plist_coll);

    return 0;
}
