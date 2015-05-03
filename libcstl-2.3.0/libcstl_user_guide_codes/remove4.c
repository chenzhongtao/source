/*
 * remove4.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    int i = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init(plist_coll);

    for(i = 1; i <= 6; ++i)
    {
        list_push_back(plist_coll, i);
        list_push_front(plist_coll, i);
    }

    /* 
     * remove all elements with value 3
     * - poor performance
     */
    list_erase_range(plist_coll,
        algo_remove(list_begin(plist_coll), list_end(plist_coll), 3),
        list_end(plist_coll));

    /*
     * remove all elements with value 4
     * - good performance
     */
    list_remove(plist_coll, 4);

    list_destroy(plist_coll);

    return 0;
}
