/*
 * list_begin.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;

    if(plist_l1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);

    list_push_back(plist_l1, 1);
    list_push_back(plist_l1, 2);

    it_l = list_begin(plist_l1);
    printf("The first element of l1 is %d\n", *(int*)iterator_get_pointer(it_l));

    *(int*)iterator_get_pointer(it_l) = 20;
    printf("The first element of l1 is now %d\n", *(int*)iterator_get_pointer(it_l));

    list_destroy(plist_l1);

    return 0;
}
