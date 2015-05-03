/*
 * slist_unique.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);
    slist_t* pslist_l2 = create_slist(int);
    slist_t* pslist_l3 = create_slist(int);
    slist_iterator_t it_l;

    if(pslist_l1 == NULL || pslist_l2 == NULL || pslist_l3 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);
    slist_init(pslist_l2);
    slist_init(pslist_l3);

    slist_push_front(pslist_l1, -10);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, -10);

    slist_assign(pslist_l2, pslist_l1);
    slist_assign(pslist_l3, pslist_l1);

    printf("The initial slist is l1 =");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_unique(pslist_l2);
    printf("After removing successive duplicate elements, l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_unique_if(pslist_l3, fun_not_equal_int);
    printf("After removing successive unequal elements, l3 =");
    for(it_l = slist_begin(pslist_l3); !iterator_equal(it_l, slist_end(pslist_l3)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);
    slist_destroy(pslist_l3);

    return 0;
}
