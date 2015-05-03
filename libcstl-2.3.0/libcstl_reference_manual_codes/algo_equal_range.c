/*
 * algo_equal_range.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

/* Return whether modulus of elem1 is less than modulus of elem2 */
static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output);

int main(int argc, char* argv[])
{
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_iterator_t it_v;
    range_t r_result;
    int i = 0;

    if(pvec_v1 == NULL || pvec_v2 == NULL || pvec_v3 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1);
    vector_init(pvec_v2);
    vector_init(pvec_v3);

    for(i = -1; i <= 4; ++i)
    {
        vector_push_back(pvec_v1, i);
    }
    for(i = -3; i <= 0; ++i)
    {
        vector_push_back(pvec_v1, i);
    }

    algo_sort(vector_begin(pvec_v1), vector_end(pvec_v1));
    printf("Original vector v1 with range sorted by the "
           "binary predicate less than is v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, vector_end(pvec_v1));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_assign(pvec_v2, pvec_v1);
    algo_sort_if(vector_begin(pvec_v2), vector_end(pvec_v2), fun_greater_int);
    printf("Original vector v2 with range sorted by the "
           "binary predicate greater than is v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, vector_end(pvec_v2));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_assign(pvec_v3, pvec_v1);
    algo_sort_if(vector_begin(pvec_v3), vector_end(pvec_v3), _mod_lesser);
    printf("Original vector v3 with range sorted by the "
           "binary predicate greater than is v3 = ( ");
    for(it_v = vector_begin(pvec_v3);
        !iterator_equal(it_v, vector_end(pvec_v3));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* equal_range of 3 in v1 with default binary predicate less than */
    r_result = algo_equal_range(vector_begin(pvec_v1), vector_end(pvec_v1), 3);
    printf("The lower_bound in v1 for the element with a value of 3 is: %d.\n",
        *(int*)iterator_get_pointer(r_result.it_begin));
    printf("The upper_bound in v1 for the element with a value of 3 is: %d.\n",
        *(int*)iterator_get_pointer(r_result.it_end));
    printf("The equal_range in v1 for the element with a value of 3 is: ( ");
    for(it_v = r_result.it_begin;
        !iterator_equal(it_v, r_result.it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* equal_range of 3 in v2 with the binary predicate greater than */
    r_result = algo_equal_range_if(vector_begin(pvec_v2), vector_end(pvec_v2), 3, fun_greater_int);
    printf("The lower_bound in v2 for the element with a value of 3 is: %d.\n",
        *(int*)iterator_get_pointer(r_result.it_begin));
    printf("The upper_bound in v2 for the element with a value of 3 is: %d.\n",
        *(int*)iterator_get_pointer(r_result.it_end));
    printf("The equal_range in v2 for the element with a value of 3 is: ( ");
    for(it_v = r_result.it_begin;
        !iterator_equal(it_v, r_result.it_end);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* equal_range of 3 in v3 with the binary predicate _mod_lesser */
    r_result = algo_equal_range_if(vector_begin(pvec_v3), vector_end(pvec_v3), 3, _mod_lesser);
    printf("The lower_bound in v3 for the element with a value of 3 is: %d.\n",
        *(int*)iterator_get_pointer(r_result.it_begin));
    printf("The upper_bound in v3 for the element with a value of 3 is: %d.\n",
        *(int*)iterator_get_pointer(r_result.it_end));
    printf("The equal_range in v3 for the element with a value of 3 is: ( ");
    for(it_v = r_result.it_begin;
        !iterator_equal(it_v, r_result.it_end);
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

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ? true : false;
}
