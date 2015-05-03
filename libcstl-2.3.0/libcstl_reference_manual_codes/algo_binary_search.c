/*
 * algo_binary_search.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

/* Return whether modulus of elem1 is less than modulus of elem2 */
static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output);

int main(int argc, char* argv[])
{
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;
    vector_t* pvec_v1 = create_vector(int);
    vector_iterator_t it_v;
    int i = 0;

    if(plist_l1 == NULL || pvec_v1 == NULL)
    {
        return -1;
    }

    list_init(plist_l1);
    vector_init(pvec_v1);

    list_push_back(plist_l1, 50);
    list_push_back(plist_l1, 10);
    list_push_back(plist_l1, 30);
    list_push_back(plist_l1, 20);
    list_push_back(plist_l1, 25);
    list_push_back(plist_l1, 5);
    list_sort(plist_l1);

    printf("l1 = ( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    if(algo_binary_search(list_begin(plist_l1), list_end(plist_l1), 10))
    {
        printf("There is an element in list l1 with a value equal to 10.\n");
    }
    else
    {
        printf("There is no element in list l1 with a value equal to 10.\n");
    }

    /* a binary_search under the binary predicate greater */
    list_sort_if(plist_l1, fun_greater_int);
    if(algo_binary_search_if(list_begin(plist_l1), list_end(plist_l1), 10, fun_greater_int))
    {
        printf("There is an element in list l1 with a value equal to 10 under greater than.\n");
    }
    else
    {
        printf("There is no element in list l1 with a value equal to 10 under greater than.\n");
    }

    /* a binary_search under the user-defined binary predicate mod_lesser */
    for(i = -2; i <= 4; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    algo_sort_if(vector_begin(pvec_v1), vector_end(pvec_v1), _mod_lesser);

    printf("Ordred under mod_lesser, vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    if(algo_binary_search_if(vector_begin(pvec_v1), vector_end(pvec_v1), -3, _mod_lesser))
    {
        printf("There is an element with a value equal to -3 under mod_lesser.\n");
    }
    else
    {
        printf("There is no element with a value equal to -3 under mod_lesser.\n");
    }

    list_destroy(plist_l1);
    vector_destroy(pvec_v1);

    return 0;
}

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ? true : false;
}
