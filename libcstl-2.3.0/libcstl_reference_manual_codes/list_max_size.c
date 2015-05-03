/*
 * list_max_size.c
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

    printf("Maximum possible length of the list is %d\n", list_max_size(plist_l1));

    list_destroy(plist_l1);

    return 0;
}
