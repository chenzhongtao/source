/*
 * list_end.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;

    if(plist_l1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);

    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 30);

    it_l = list_end(plist_l1);
    it_l = iterator_prev(it_l);
    printf("The last integer of l1 is %d\n", *(int*)iterator_get_pointer(it_l));

    it_l = iterator_prev(it_l);
    *(int*)iterator_get_pointer(it_l) = 400;
    printf("The new nex-to-last integer of l1 is %d\n", *(int*)iterator_get_pointer(it_l));

    printf("The list is now:");
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_destroy(plist_l1);

    return 0;
}
