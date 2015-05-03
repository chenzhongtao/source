/*
 * list_clear.c
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
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);

    printf("The size of the list is initially %d\n", list_size(plist_l1));
    list_clear(plist_l1);
    printf("The size of the list after clearing is %d\n", list_size(plist_l1));

    list_destroy(plist_l1);

    return 0;
}
