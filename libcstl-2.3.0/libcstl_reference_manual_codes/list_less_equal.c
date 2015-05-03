/*
 * list_less_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_t* plist_l2 = create_list(int);

    if(plist_l1 == NULL || plist_l2 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);
    list_init(plist_l2);

    list_push_back(plist_l1, 1);
    list_push_back(plist_l1, 2);
    list_push_back(plist_l1, 4);

    list_push_back(plist_l2, 1);
    list_push_back(plist_l2, 3);

    if(list_less_equal(plist_l1, plist_l2))
    {
        printf("List l1 is less than or equal to list l2.\n");
    }
    else
    {
        printf("List l1 is greater than list l2.\n");
    }

    list_destroy(plist_l1);
    list_destroy(plist_l2);

    return 0;
}
