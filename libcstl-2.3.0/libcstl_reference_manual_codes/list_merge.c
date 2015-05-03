/*
 * list_merge.c
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

    if(plist_l1 == NULL || plist_l2 == NULL || plist_l2 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);
    list_init(plist_l2);
    list_init(plist_l3);

    list_push_back(plist_l1, 3);
    list_push_back(plist_l1, 6);
    list_push_back(plist_l2, 2);
    list_push_back(plist_l2, 4);
    list_push_back(plist_l3, 5);
    list_push_back(plist_l3, 1);

    printf("l1 =");
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    printf("l2 =");
    for(it_l = list_begin(plist_l2); !iterator_equal(it_l, list_end(plist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_merge(plist_l2, plist_l1); /* Merge l1 into l2 in (default) ascending order */
    list_sort_if(plist_l2, fun_greater_int);
    printf("After merging l1 with l2 and sorting with >: l2 =");
    for(it_l = list_begin(plist_l2); !iterator_equal(it_l, list_end(plist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    printf("l3 =");
    for(it_l = list_begin(plist_l3); !iterator_equal(it_l, list_end(plist_l3)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_merge_if(plist_l2, plist_l3, fun_greater_int);
    printf("After merging l3 with l2 according to the '>' comparison relation: l2 =");
    for(it_l = list_begin(plist_l2); !iterator_equal(it_l, list_end(plist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_destroy(plist_l1);
    list_destroy(plist_l2);
    list_destroy(plist_l3);

    return 0;
}
