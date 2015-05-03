/*
 * list_pop_front.c
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
    list_push_back(plist_l1, 2);

    printf("The first element is: %d\n", *(int*)list_front(plist_l1));
    printf("The second element is: %d\n", *(int*)list_back(plist_l1));

    list_pop_front(plist_l1);
    printf("After deleting the element at the beginning of the list, the first element is: %d\n", *(int*)list_front(plist_l1));

    list_destroy(plist_l1);

    return 0;
}
