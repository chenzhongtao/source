/*
 * list_push_back.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);

    if(plist_l1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);

    list_push_back(plist_l1, 1);
    if(list_size(plist_l1) != 0)
    {
        printf("Last element: %d\n", *(int*)list_back(plist_l1));
    }

    list_push_back(plist_l1, 2);
    if(list_size(plist_l1) != 0)
    {
        printf("New last element: %d\n", *(int*)list_back(plist_l1));
    }

    list_destroy(plist_l1);

    return 0;
}
