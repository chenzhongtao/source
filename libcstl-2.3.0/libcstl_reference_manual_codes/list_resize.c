/*
 * list_resize.c
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

    list_resize_elem(plist_l1, 4, 40);
    printf("The size of l1 is %d\n", list_size(plist_l1));
    printf("The value of the last element is %d\n", *(int*)list_back(plist_l1));

    list_resize(plist_l1, 5);
    printf("The size of l1 is now %d\n", list_size(plist_l1));
    printf("The value of the last element is now %d\n", *(int*)list_back(plist_l1));

    list_resize(plist_l1, 2);
    printf("The reduced size of l1 is %d\n", list_size(plist_l1));
    printf("The value of the last element is now %d\n", *(int*)list_back(plist_l1));

    list_destroy(plist_l1);

    return 0;
}
