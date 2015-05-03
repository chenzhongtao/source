/*
 * slist_remove_if.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    slist_t* pslist_l1 = create_slist(int);
    slist_iterator_t it_l;

    if(pslist_l1 == NULL)
    {
        return -1;
    }

    slist_init(pslist_l1);

    slist_push_front(pslist_l1, 3);
    slist_push_front(pslist_l1, 4);
    slist_push_front(pslist_l1, 5);
    slist_push_front(pslist_l1, 6);
    slist_push_front(pslist_l1, 7);
    slist_push_front(pslist_l1, 8);

    printf("The initial slist is l1 =");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_remove_if(pslist_l1, is_odd);
    printf("After removing the odd elements, the slist becomes l1 =");
    for(it_l = slist_begin(pslist_l1); !iterator_equal(it_l, slist_end(pslist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_destroy(pslist_l1);

    return 0;
}

static void is_odd(const void* cpv_input, void* pv_output)
{
    assert(cpv_input != NULL && pv_output != NULL);
    if(*(int*)cpv_input % 2 == 1)
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}
