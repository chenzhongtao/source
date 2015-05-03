/*
 * algo_find_if.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _greater10(const void* cpv_input, void* pv_output);

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;

    if(plist_l1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);

    list_push_back(plist_l1, 40);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 30);
    list_push_back(plist_l1, 10);

    printf("l1 = ( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    it_l = algo_find_if(list_begin(plist_l1), list_end(plist_l1), _greater10);
    if(iterator_equal(it_l, list_end(plist_l1)))
    {
        printf("There is no element greater than 10 in list l1.\n");
    }
    else
    {
        printf("There is an element greater than 10 in list l1 is %d.\n",
            *(int*)iterator_get_pointer(it_l));
    }

    list_destroy(plist_l1);

    return 0;
}

static void _greater10(const void* cpv_input, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_input > 10 ? true : false;
}
