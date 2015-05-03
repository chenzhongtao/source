/*
 * advance1.c
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

    for(i = 1; i <= 9; ++i)
    {
        list_push_back(plist_coll, i);
    }

    it_pos = list_begin(plist_coll);
    /* print actual element */
    printf("%d\n", *(int*)iterator_get_pointer(it_pos));

    /* step three elements forward */
    it_pos = iterator_advance(it_pos, 3);
    /* print actual element */
    printf("%d\n", *(int*)iterator_get_pointer(it_pos));

    /* step one element backward */
    it_pos = iterator_advance(it_pos, -1);
    /* print actual element */
    printf("%d\n", *(int*)iterator_get_pointer(it_pos));

    list_destroy(plist_coll);

    return 0;
}
