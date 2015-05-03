/*
 * algo_adjacent_find.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output);

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;

    if(plist_l1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);

    list_push_back(plist_l1, 50);
    list_push_back(plist_l1, 40);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 20);

    printf("list l1 = ( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    it_l = algo_adjacent_find(list_begin(plist_l1), list_end(plist_l1));
    if(iterator_equal(it_l, list_end(plist_l1)))
    {
        printf("There are not two adjacent elements that are equal.\n");
    }
    else
    {
        printf("There are two adjacent elements that are equal.\n"
               "They have a value of %d.\n", *(int*)iterator_get_pointer(it_l));
    }

    it_l = algo_adjacent_find_if(list_begin(plist_l1), list_end(plist_l1), _twice);
    if(iterator_equal(it_l, list_end(plist_l1)))
    {
        printf("There are not two adjacent elements where the second is twice the first.\n");
    }
    else
    {
        printf("There are two adjacent elements where the second is twice the first.\n"
               "They have values of %d & %d.\n",
               *(int*)iterator_get_pointer(it_l),
               *(int*)iterator_get_pointer(iterator_next(it_l)));
    }

    list_destroy(plist_l1);

    return 0;
}

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first * 2 == *(int*)cpv_second ? true : false;
}
