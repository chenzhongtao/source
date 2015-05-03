/*
 * inner1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cnumeric.h>
#include <cstl/cfunctional.h>

int main(int argc, char* argv[])
{
    list_t* plist_coll = create_list(int);
    iterator_t it_pos;
    int n_result = 0;

    if(plist_coll == NULL)
    {
        return -1;
    }

    list_init_n(plist_coll, 6);
    algo_iota(list_begin(plist_coll), list_end(plist_coll), 1);

    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");

    algo_inner_product(list_begin(plist_coll), list_end(plist_coll),
        list_begin(plist_coll), 0, &n_result);
    printf("inner product: %d\n", n_result);

    algo_inner_product_if(list_begin(plist_coll), list_end(plist_coll),
        list_begin(plist_coll), 1, fun_multiplies_int, fun_plus_int, &n_result);
    printf("product of sums: %d\n", n_result);

    list_destroy(plist_coll);

    return 0;
}
