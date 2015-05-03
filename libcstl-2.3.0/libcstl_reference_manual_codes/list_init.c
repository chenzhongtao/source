/*
 * list_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>

int main(int argc, char* argv[])
{
    list_t* plist_l0 = create_list(int);
    list_t* plist_l1 = create_list(int);
    list_t* plist_l2 = create_list(int);
    list_t* plist_l3 = create_list(int);
    list_t* plist_l4 = create_list(int);
    list_iterator_t it_l;

    if(plist_l0 == NULL || plist_l1 == NULL || plist_l2 == NULL || plist_l3 == NULL || plist_l4 == NULL)
    {
        return -1;
    }

    /* Create an empty list l0 */
    list_init(plist_l0);

    /* Create a list l1 with 3 elements of default value 0 */
    list_init_n(plist_l1, 3);

    /* Create a list l2 with 5 elements of value 2 */
    list_init_elem(plist_l2, 5, 2);

    /* Create a copy, list l3, of list l2 */
    list_init_copy(plist_l3, plist_l2);

    /* Create a list l4 by copying the range l3[first, last) */
    list_init_copy_range(plist_l4, iterator_advance(list_begin(plist_l3), 2), list_end(plist_l3));

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

    printf("l3 =");
    for(it_l = list_begin(plist_l3); !iterator_equal(it_l, list_end(plist_l3)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    printf("l4 =");
    for(it_l = list_begin(plist_l4); !iterator_equal(it_l, list_end(plist_l4)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    list_destroy(plist_l0);
    list_destroy(plist_l1);
    list_destroy(plist_l2);
    list_destroy(plist_l3);
    list_destroy(plist_l4);

    return 0;
}
