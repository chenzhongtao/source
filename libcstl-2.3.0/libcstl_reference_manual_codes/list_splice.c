/*
 * list_splice.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_t* plist_l2 = create_list(int);
    list_t* plist_l3 = create_list(int);
    list_t* plist_l4 = create_list(int);
    list_iterator_t it_l;

    if(plist_l1 == NULL || plist_l2 == NULL || plist_l3 == NULL || plist_l4 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);
    list_init(plist_l2);
    list_init(plist_l3);
    list_init(plist_l4);

    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 11);
    list_push_back(plist_l2, 12);
    list_push_back(plist_l2, 20);
    list_push_back(plist_l2, 21);
    list_push_back(plist_l3, 30);
    list_push_back(plist_l3, 31);
    list_push_back(plist_l4, 40);
    list_push_back(plist_l4, 41);
    list_push_back(plist_l4, 42);

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

    list_splice(plist_l2, iterator_next(list_begin(plist_l2)), plist_l1);
    printf("After splicing l1 into l2: l2 =");
    for(it_l = list_begin(plist_l2); !iterator_equal(it_l, list_end(plist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_splice_pos(plist_l2, iterator_next(list_begin(plist_l2)), plist_l3, list_begin(plist_l3));
    printf("After splicing the first element of l3 into l2: l2 =");
    for(it_l = list_begin(plist_l2); !iterator_equal(it_l, list_end(plist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_splice_range(plist_l2, iterator_next(list_begin(plist_l2)), plist_l4, list_begin(plist_l4), iterator_prev(list_end(plist_l4)));
    printf("After splicing a range of l4 into l2: l2 =");
    for(it_l = list_begin(plist_l2); !iterator_equal(it_l, list_end(plist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_destroy(plist_l1);
    list_destroy(plist_l2);
    list_destroy(plist_l3);
    list_destroy(plist_l4);

    return 0;
}
