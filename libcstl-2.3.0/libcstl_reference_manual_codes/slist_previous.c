/*
 * slist_previous.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);
    slist_iterator_t it_l;

    if(pslist_l1 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);

    slist_push_front(pslist_l1, 1);
    slist_push_front(pslist_l1, 2);

    it_l = slist_end(pslist_l1);
    it_l = slist_previous(pslist_l1, it_l);
    printf("The last element of list is %d\n", *(int*)iterator_get_pointer(it_l));

    slist_destroy(pslist_l1);

    return 0;
}
