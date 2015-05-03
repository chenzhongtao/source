/*
 * lexico1.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/clist.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>

static void _print_list(const void* cpv_input, void* pv_output)
{
    list_t* plist_coll = (list_t*)cpv_input;
    iterator_t it_pos;
    for(it_pos = list_begin(plist_coll);
        !iterator_equal(it_pos, list_end(plist_coll));
        it_pos = iterator_next(it_pos))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_pos));
    }
    printf("\n");
}

static void _less_for_coll(const void* cpv_first,
    const void* cpv_second, void* pv_output)
{
    list_t* plist_coll1 = (list_t*)cpv_first;
    list_t* plist_coll2 = (list_t*)cpv_second;

    if(algo_lexicographical_compare(
        list_begin(plist_coll1), list_end(plist_coll1),
        list_begin(plist_coll2), list_end(plist_coll2)))
    {
        *(bool_t*)pv_output = true;
    }
    else
    {
        *(bool_t*)pv_output = false;
    }
}

int main(int argc, char* argv[])
{
    list_t* plist_c1 = create_list(int);
    list_t* plist_c2 = create_list(int);
    list_t* plist_c3 = create_list(int);
    list_t* plist_c4 = create_list(int);
    vector_t* pvec_cc = create_vector(list_t<int>);
    int i = 0;

    if(plist_c1 == NULL || plist_c2 == NULL || plist_c3 == NULL ||
       plist_c4 == NULL || pvec_cc == NULL)
    {
        return -1;
    }

    list_init(plist_c1);
    list_init(plist_c2);
    list_init(plist_c3);
    list_init(plist_c4);
    vector_init(pvec_cc);

    for(i = 1; i <= 5; ++i)
    {
        list_push_back(plist_c1, i);
    }
    list_assign(plist_c2, plist_c1);
    list_assign(plist_c3, plist_c1);
    list_assign(plist_c4, plist_c1);
    list_push_back(plist_c1, 7);
    list_push_back(plist_c3, 2);
    list_push_back(plist_c3, 0);
    list_push_back(plist_c4, 2);

    vector_push_back(pvec_cc, plist_c1);
    vector_push_back(pvec_cc, plist_c2);
    vector_push_back(pvec_cc, plist_c3);
    vector_push_back(pvec_cc, plist_c4);
    vector_push_back(pvec_cc, plist_c3);
    vector_push_back(pvec_cc, plist_c1);
    vector_push_back(pvec_cc, plist_c4);
    vector_push_back(pvec_cc, plist_c2);

    algo_for_each(vector_begin(pvec_cc), vector_end(pvec_cc), _print_list);
    printf("\n");
    algo_sort_if(vector_begin(pvec_cc), vector_end(pvec_cc), _less_for_coll);
    algo_for_each(vector_begin(pvec_cc), vector_end(pvec_cc), _print_list);

    list_destroy(plist_c1);
    list_destroy(plist_c2);
    list_destroy(plist_c3);
    list_destroy(plist_c4);
    vector_destroy(pvec_cc);

    return 0;
}
