/*
 * slist_erase.c
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
    slist_push_front(pslist_l1, 40);
    slist_push_front(pslist_l1, 50);

    printf("The initial slist is:");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_erase(pslist_l1, slist_begin(pslist_l1));
    printf("After erasing the first element, the slist becomes:");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_erase_range(pslist_l1, iterator_next(slist_begin(pslist_l1)), slist_end(pslist_l1));
    printf("After erasing all elements but the first, the slist becomes:");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_clear(pslist_l1);
    slist_push_front(pslist_l1, 10);
    slist_push_front(pslist_l1, 20);
    slist_push_front(pslist_l1, 30);
    slist_push_front(pslist_l1, 40);
    slist_push_front(pslist_l1, 50);

    printf("After resetting, the slist becomes:");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_erase_after(pslist_l1, slist_begin(pslist_l1));
    printf("After erasing the element following the first, the slist becomes:");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_erase_after_range(pslist_l1, slist_begin(pslist_l1), slist_end(pslist_l1));
    printf("After erasing all elements but the first, the slist becomes:");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_destroy(pslist_l1);

    return 0;
}
