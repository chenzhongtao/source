/*
 * algo_lexicographical_compare.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/clist.h>
#include <cstl/calgorithm.h>

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output);

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_iterator_t it_v;
    list_t* plist_l1 = create_list(int);
    list_iterator_t it_l;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || plist_l1 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    list_init(plist_l1);

    for(i = 0; i < 6; ++i)
    {
        vector_push_back(pvec_v1, i * 5);
        vector_push_back(pvec_v2, i * 10);
    }
    for(i = 0; i < 7; ++i)
    {
        list_push_back(plist_l1, i * 5);
    }

    printf("Vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("Vector v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("List l1 = ( ");
    for(it_l = list_begin(plist_l1);
        !iterator_equal(it_l, list_end(plist_l1));
        it_l = iterator_next(it_l))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_l));
    }
    printf(")\n");

    /* Self lexicographical_comparison of v1 under identity */
    if(algo_lexicographical_compare(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v1), vector_end(pvec_v1)))
    {
        printf("Vector v1 is lexicographically less than v1.\n");
    }
    else
    {
        printf("Vector v1 is not lexicographically less than v1.\n");
    }

    /* lexicographical_comparison of v1 and l1 under identity */
    if(algo_lexicographical_compare(vector_begin(pvec_v1), vector_end(pvec_v1),
        list_begin(plist_l1), list_end(plist_l1)))
    {
        printf("Vector v1 is lexicographically less than l1.\n");
    }
    else
    {
        printf("Vector v1 is not lexicographically less than l1.\n");
    }

    if(algo_lexicographical_compare_if(vector_begin(pvec_v1), vector_end(pvec_v1),
        vector_begin(pvec_v2), vector_end(pvec_v2), _twice))
    {
        printf("Vector v1 is lexicographically less than v2 under twice.\n");
    }
    else
    {
        printf("Vector v1 is not lexicographically less than v2 under twice.\n");
    }

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    list_destroy(plist_l1);

    return 0;
}

static void _twice(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = *(int*)cpv_first * 2 < *(int*)cpv_second ? true : false;
}
