/*
 * list_front.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    int* pn_i = NULL;
    int* pn_j = NULL;

    if(plist_l1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);

    list_push_back(plist_l1, 10);

    pn_i = (int*)list_front(plist_l1);
    pn_j = (int*)list_front(plist_l1);

    printf("The first integer of l1 is %d\n", *pn_i);
    (*pn_i)++;
    printf("The modified first integer of l1 is %d\n", *pn_j);

    list_destroy(plist_l1);

    return 0;
}
