/*
 * slist_equal.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);
    slist_t* pslist_l2 = create_slist(int);

    if(pslist_l1 == NULL || pslist_l2 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);
    slist_init(pslist_l2);

    slist_push_front(pslist_l1, 1);
    slist_push_front(pslist_l2, 1);

    if(slist_equal(pslist_l1, pslist_l2))
    {
        printf("The slists are equal.\n");
    }
    else
    {
        printf("The slists are not equal.\n");
    }

    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);

    return 0;
}
