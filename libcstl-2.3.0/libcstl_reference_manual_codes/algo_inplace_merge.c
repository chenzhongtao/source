/*
 * algo_inplace_merge.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ? true : false;
}

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_iterator_t it_v;
    vector_iterator_t it_break1;
    vector_iterator_t it_break2;
    vector_iterator_t it_break3;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    vector_init(pvec_v3);

    for(i = 0; i <= 5; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = -5; i <= 0; ++i)
    {
        vector_push_back(pvec_v1, i);
    }

    printf("Original vector v1 with subrangs sorted by the\n"
           "binary predicate less than is v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Constructing vector v2 with range sorted by greater */
    vector_assign(pvec_v2, pvec_v1);
    it_break2 = algo_find(vector_begin(pvec_v2), vector_end(pvec_v2), -5);
    algo_sort_if(vector_begin(pvec_v2), it_break2, fun_greater_int);
    algo_sort_if(it_break2, vector_end(pvec_v2), fun_greater_int);
    printf("Original vector v2 with subrangs sorted by the\n"
           "binary predicate greater than is v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Constructing vector v3 with range sorted by greater */
    vector_assign(pvec_v3, pvec_v1);
    it_break3 = algo_find(vector_begin(pvec_v3), vector_end(pvec_v3), -5);
    algo_sort_if(vector_begin(pvec_v3), it_break3, _mod_lesser);
    algo_sort_if(it_break3, vector_end(pvec_v3), fun_greater_int);
    printf("Original vector v3 with subrangs sorted by the\n"
           "binary predicate greater than is v3 = ( ");
    for(it_v = vector_begin(pvec_v3);
        !iterator_equal(it_v, vector_end(pvec_v3));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    it_break1 = algo_find(vector_begin(pvec_v1), vector_end(pvec_v1), -5);
    algo_inplace_merge(vector_begin(pvec_v1), it_break1, vector_end(pvec_v1));
    printf("Merged inplace with default order,\nvector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To merge inplace in desceding order, specify binary predicate greater */
    algo_inplace_merge_if(vector_begin(pvec_v2), it_break2,
        vector_end(pvec_v2), fun_greater_int);
    printf("Merged inplace with default order,\nvector v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Applying a user defined binary predicate mod_lesser */
    algo_inplace_merge_if(vector_begin(pvec_v3), it_break3,
        vector_end(pvec_v3), _mod_lesser);
    printf("Merged inplace with default order,\nvector v3 = ( ");
    for(it_v = vector_begin(pvec_v3);
        !iterator_equal(it_v, vector_end(pvec_v3));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3);

    return 0;
}
