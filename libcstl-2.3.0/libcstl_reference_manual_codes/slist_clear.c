/*
 * slist_clear.c
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
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);

    printf("The size of the slist is initially %d\n", slist_size(pslist_l1));
    slist_clear(pslist_l1);
    printf("The size of slist after clearing is %d\n", slist_size(pslist_l1));

    slist_destroy(pslist_l1);

    return 0;
}
