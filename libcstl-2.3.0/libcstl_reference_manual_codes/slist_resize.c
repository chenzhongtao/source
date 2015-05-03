/*
 * slist_resize.c
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

    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);

    slist_resize_elem(pslist_l1, 4, 40);
    it_l = slist_previous(pslist_l1, slist_end(pslist_l1));
    printf("The size of l1 is %d\n", slist_size(pslist_l1));
    printf("The value of the last element is %d\n", *(int*)iterator_get_pointer(it_l));

    slist_resize(pslist_l1, 5);
    it_l = slist_previous(pslist_l1, slist_end(pslist_l1));
    printf("The size of l1 is now %d\n", slist_size(pslist_l1));
    printf("The value of the last element is now %d\n", *(int*)iterator_get_pointer(it_l));

    slist_resize(pslist_l1, 2);
    it_l = slist_previous(pslist_l1, slist_end(pslist_l1));
    printf("The reduced size of l1 is %d\n", slist_size(pslist_l1));
    printf("The value of the last element is now %d\n", *(int*)iterator_get_pointer(it_l));

    slist_destroy(pslist_l1);

    return 0;
}
