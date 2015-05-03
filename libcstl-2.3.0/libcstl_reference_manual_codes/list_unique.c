/*
 * list_unique.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_t* plist_l2 = create_list(int);
    list_t* plist_l3 = create_list(int);
    list_iterator_t it_l;

    if(plist_l1 == NULL || plist_l2 == NULL || plist_l3 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);
    list_init(plist_l2);
    list_init(plist_l3);

    list_push_back(plist_l1, -10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, -10);

    list_assign(plist_l2, plist_l1);
    list_assign(plist_l3, plist_l1);

    printf("The initial list is l1 =");
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_unique(plist_l2);
    printf("After removing successive duplicate elements, l2 =");
    for(it_l = list_begin(plist_l2); !iterator_equal(it_l, list_end(plist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_unique_if(plist_l3, fun_not_equal_int);
    printf("After removing successive unequal elements, l3 =");
    for(it_l = list_begin(plist_l3); !iterator_equal(it_l, list_end(plist_l3)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_destroy(plist_l1);
    list_destroy(plist_l2);
    list_destroy(plist_l3);

    return 0;
}
