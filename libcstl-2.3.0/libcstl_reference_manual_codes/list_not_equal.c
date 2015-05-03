/*
 * list_not_equal.c
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
    list_push_back(plist_l2, 2);

    if(list_not_equal(plist_l1, plist_l2))
    {
        printf("Lists not equal.\n");
    }
    else
    {
        printf("Lists equal.\n");
    }

    list_destroy(plist_l1);
    list_destroy(plist_l2);

    return 0;
}
