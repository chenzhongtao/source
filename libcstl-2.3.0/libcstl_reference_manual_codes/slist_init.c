/*
 * slist_init.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cslist.h>

int main(int argc, char* argv[])
{
    slist_t* pslist_l0 = create_slist(int);
    slist_t* pslist_l1 = create_slist(int);
    slist_t* pslist_l2 = create_slist(int);
    slist_t* pslist_l3 = create_slist(int);
    slist_t* pslist_l4 = create_slist(int);
    slist_iterator_t it_l;

    if(pslist_l0 == NULL || pslist_l1 == NULL || pslist_l2 == NULL || pslist_l3 == NULL || pslist_l4 == NULL)
    {
        return -1;
    }

    /* Create an empty slist l0 */
    slist_init(pslist_l0);

    /* Create a slist l1 with 3 elements of default value 0 */
    slist_init_n(pslist_l1, 3);

    /* Create a slist l2 with 5 elements of value 2 */
    slist_init_elem(pslist_l2, 5, 2);

    /* Create a copy, slist l3, of slist l3 */
    slist_init_copy(pslist_l3, pslist_l2);

    /* Create a slist l4 by copying the range l3[first, last) */
    slist_init_copy_range(pslist_l4, iterator_advance(slist_begin(pslist_l3), 3), slist_end(pslist_l3));

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

    printf("l3 =");
    for(it_l = slist_begin(pslist_l3); !iterator_equal(it_l, slist_end(pslist_l3)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    printf("l4 =");
    for(it_l = slist_begin(pslist_l4); !iterator_equal(it_l, slist_end(pslist_l4)); it_l = iterator_next(it_l))
    {
        printf(" %d", *(int*)iterator_get_pointer(it_l));
    }
    printf("\n");

    slist_destroy(pslist_l0);
    slist_destroy(pslist_l1);
    slist_destroy(pslist_l2);
    slist_destroy(pslist_l3);
    slist_destroy(pslist_l4);

    return 0;
}
