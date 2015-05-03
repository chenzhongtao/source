/*
 * slist_splice.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);
    slist_t* pslist_l2 = create_slist(int);
    slist_t* pslist_l3 = create_slist(int);
    slist_t* pslist_l4 = create_slist(int);
    slist_t* pslist_l5 = create_slist(int);
    slist_t* pslist_l6 = create_slist(int);
    slist_iterator_t it_l;

    if(pslist_l1 == NULL || pslist_l2 == NULL || pslist_l3 == NULL || pslist_l4 == NULL || pslist_l5 == NULL || pslist_l6 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);
    slist_init(pslist_l2);
    slist_init(pslist_l3);
    slist_init(pslist_l4);
    slist_init(pslist_l5);
    slist_init(pslist_l6);

    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 11);
    slist_push_front(pslist_l2, 12);
    slist_push_front(pslist_l2, 20);
    slist_push_front(pslist_l2, 21);
    slist_push_front(pslist_l3, 30);
    slist_push_front(pslist_l3, 31);
    slist_push_front(pslist_l4, 40);
    slist_push_front(pslist_l4, 41);
    slist_push_front(pslist_l4, 42);
    slist_push_front(pslist_l5, 55);
    slist_push_front(pslist_l5, 56);
    slist_push_front(pslist_l5, 57);
    slist_push_front(pslist_l6, 62);
    slist_push_front(pslist_l6, 65);
    slist_push_front(pslist_l6, 66);
    slist_push_front(pslist_l6, 67);

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

    slist_splice(pslist_l2, iterator_next(slist_begin(pslist_l2)), pslist_l1);
    printf("After splicing l1 into l2: l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_splice_pos(pslist_l2, iterator_next(slist_begin(pslist_l2)), pslist_l3, slist_begin(pslist_l3));
    printf("After splicing the first element of l3 into l2: l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_splice_range(pslist_l2, iterator_next(slist_begin(pslist_l2)), pslist_l4, slist_begin(pslist_l4), slist_end(pslist_l4));
    printf("After splicing a range of l4 into l2: l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_splice_after_pos(pslist_l2, slist_begin(pslist_l2), pslist_l5, slist_begin(pslist_l5));
    printf("After splicing the element following the first of l5 into l2: l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_splice_after_range(pslist_l2, slist_begin(pslist_l2), pslist_l6, slist_begin(pslist_l6), iterator_advance(slist_begin(pslist_l6), 2));
    printf("After splicing a range of l6 into l2: l2 =");
    for(it_l = slist_begin(pslist_l2); !iterator_equal(it_l, slist_end(pslist_l2)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);
    slist_destroy(pslist_l3);
    slist_destroy(pslist_l4);
    slist_destroy(pslist_l5);
    slist_destroy(pslist_l6);

    return 0;
}
