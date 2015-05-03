/*
 * slist_merge.c
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

    if(pslist_l1 == NULL || pslist_l2 == NULL || pslist_l2 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);
    slist_init(pslist_l2);
    slist_init(pslist_l3);

    slist_push_front(pslist_l1, 6);
    slist_push_front(pslist_l1, 3);
    slist_push_front(pslist_l2, 4);
    slist_push_front(pslist_l2, 2);
    slist_push_front(pslist_l3, 1);
    slist_push_front(pslist_l3, 5);

    printf("l1 =");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    printf("l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_merge(pslist_l2, pslist_l1); /* Merge l1 into l2 in (default) ascending order */
    slist_sort_if(pslist_l2, fun_greater_int);
    printf("After merging l1 with l2 and sorting with >: l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    printf("l3 =");
    for(it_l = slist_begin(pslist_l3); !iterator_equal(it_l, slist_end(pslist_l3)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_merge_if(pslist_l2, pslist_l3, fun_greater_int);
    printf("After merging l3 with l2 according to the '>' comparison relation: l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);
    slist_destroy(pslist_l3);

    return 0;
}
