/*
 * slist_empty.c
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

    slist_push_front(pslist_l1, 10);
    if(slist_empty(pslist_l1))
    {
        printf("The slist is empty.\n");
    }
    else
    {
        printf("The slist is not empty.\n");
    }

    slist_destroy(pslist_l1);

    return 0;
}
