/*
 * list_remove_if.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

static void is_odd(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;

    if(plist_l1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);

    list_push_back(plist_l1, 3);
    list_push_back(plist_l1, 4);
    list_push_back(plist_l1, 5);
    list_push_back(plist_l1, 6);
    list_push_back(plist_l1, 7);
    list_push_back(plist_l1, 8);

    printf("The initial list is l1 =");
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_remove_if(plist_l1, is_odd);
    printf("After removing the odd elements, the list becomes l1 =");
    for(it_l = list_begin(plist_l1); !iterator_equal(it_l, list_end(plist_l1)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_destroy(plist_l1);

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
