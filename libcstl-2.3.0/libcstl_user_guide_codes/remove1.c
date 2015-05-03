/*
 * remove1.c
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

    /* insert element from 1 to 6 and 6 to 1 */
    for(i = 1; i <= 6; ++i)
    {
        list_push_back(plist_coll, i);
        list_push_front(plist_coll, i);
    }

    /* print all elements of the list */
    printf("Pre:  ");
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    /* remove all elements with value 3 */
    algo_remove(list_begin(plist_coll), list_end(plist_coll), 3);

    printf("Post: ");
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
