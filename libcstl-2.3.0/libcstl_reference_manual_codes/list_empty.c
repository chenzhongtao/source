/*
 * list_empty.c
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

    list_push_back(plist_l1, 10);
    if(list_empty(plist_l1))
    {
        printf("The list is empty.\n");
    }
    else
    {
        printf("The list is not empty.\n");
    }

    list_destroy(plist_l1);

    return 0;
}
