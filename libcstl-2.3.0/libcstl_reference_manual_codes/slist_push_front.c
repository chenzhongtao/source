/*
 * slist_push_front.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);

    if(pslist_l1 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);

    slist_push_front(pslist_l1, 1);
    if(slist_size(pslist_l1) != 0)
    {
        printf("First element: %d\n", *(int*)slist_front(pslist_l1));
    }

    slist_push_front(pslist_l1, 2);
    if(slist_size(pslist_l1) != 0)
    {
        printf("New first element: %d\n", *(int*)slist_front(pslist_l1));
    }

    slist_destroy(pslist_l1);

    return 0;
}
