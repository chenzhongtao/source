/*
 * algo_set_union.c
 * compile with : -lcstl
 */

#include <stdio.h>
#include <cstl/cvector.h>
#include <cstl/calgorithm.h>
#include <cstl/cfunctional.h>

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output);

int main(int argc, char* argv[])
{
    vector_t* pvec_v1a = create_vector(int);
    vector_t* pvec_v1b = create_vector(int);
    vector_t* pvec_v1 = create_vector(int);
    vector_t* pvec_v2a = create_vector(int);
    vector_t* pvec_v2b = create_vector(int);
    vector_t* pvec_v2 = create_vector(int);
    vector_t* pvec_v3a = create_vector(int);
    vector_t* pvec_v3b = create_vector(int);
    vector_t* pvec_v3 = create_vector(int);
    vector_iterator_t it_v;
    vector_iterator_t it_result;
    int i = 0;

    if(pvec_v1a == NULL || pvec_v1b == NULL || pvec_v1 == NULL ||
       pvec_v2a == NULL || pvec_v2b == NULL || pvec_v2 == NULL ||
       pvec_v3a == NULL || pvec_v3b == NULL || pvec_v3 == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1a);
    vector_init(pvec_v1b);
    vector_init(pvec_v1);
    vector_init(pvec_v2a);
    vector_init(pvec_v2b);
    vector_init(pvec_v2);
    vector_init(pvec_v3a);
    vector_init(pvec_v3b);
    vector_init(pvec_v3);

    /* Constructing vectors v1a and v1b with default less than ordering */
    for(i = -1; i <= 3; ++i)
    {
        vector_push_back(pvec_v1a, i);
    }
    for(i = -3; i <= 1; ++i)
    {
        vector_push_back(pvec_v1b, i);
    }
    vector_resize(pvec_v1, 12);
    printf("Original vector v1a with range sorted by the\n"
           "binary predicate less than is v1a = ( ");
    for(it_v = vector_begin(pvec_v1a);
        !iterator_equal(it_v, vector_end(pvec_v1a));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("Original vector v1b with range sorted by the\n"
           "binary predicate less than is v1b = ( ");
    for(it_v = vector_begin(pvec_v1b);
        !iterator_equal(it_v, vector_end(pvec_v1b));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Constructing vectors v2a and v2b with ranges sorted by greater */
    vector_assign(pvec_v2a, pvec_v1a);
    vector_assign(pvec_v2b, pvec_v1b);
    vector_assign(pvec_v2, pvec_v1);
    algo_sort_if(vector_begin(pvec_v2a), vector_end(pvec_v2a), fun_greater_int);
    algo_sort_if(vector_begin(pvec_v2b), vector_end(pvec_v2b), fun_greater_int);
    printf("Original vector v2a with range sorted by the\n"
           "binary predicate greater than is v2a = ( ");
    for(it_v = vector_begin(pvec_v2a);
        !iterator_equal(it_v, vector_end(pvec_v2a));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("Original vector v2b with range sorted by the\n"
           "binary predicate greater than is v2b = ( ");
    for(it_v = vector_begin(pvec_v2b);
        !iterator_equal(it_v, vector_end(pvec_v2b));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* Constructing vectors v3a and v3b with ranges sorted by mod_lesser */
    vector_assign(pvec_v3a, pvec_v1a);
    vector_assign(pvec_v3b, pvec_v1b);
    vector_assign(pvec_v3, pvec_v1);
    algo_sort_if(vector_begin(pvec_v3a), vector_end(pvec_v3a), _mod_lesser);
    algo_sort_if(vector_begin(pvec_v3b), vector_end(pvec_v3b), _mod_lesser);
    printf("Original vector v3a with range sorted by the\n"
           "binary predicate mod_lesser is v3a = ( ");
    for(it_v = vector_begin(pvec_v3a);
        !iterator_equal(it_v, vector_end(pvec_v3a));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");
    printf("Original vector v3b with range sorted by the\n"
           "binary predicate greater than is v3b = ( ");
    for(it_v = vector_begin(pvec_v3b);
        !iterator_equal(it_v, vector_end(pvec_v3b));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To combine int a union in ascending order with the default binary predicate less */
    it_result = algo_set_union(vector_begin(pvec_v1a), vector_end(pvec_v1a),
        vector_begin(pvec_v1b), vector_end(pvec_v1b), vector_begin(pvec_v1));
    printf("Union of source ranges with default order\n"
           "vector v1 = ( ");
    for(it_v = vector_begin(pvec_v1);
        !iterator_equal(it_v, it_result);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To combine int a union in ascending order with the specify binary predicate greater */
    it_result = algo_set_union_if(vector_begin(pvec_v2a), vector_end(pvec_v2a),
        vector_begin(pvec_v2b), vector_end(pvec_v2b), vector_begin(pvec_v2),
        fun_greater_int);
    printf("Union of source ranges with binary predicate greater order\n"
           "vector v2 = ( ");
    for(it_v = vector_begin(pvec_v2);
        !iterator_equal(it_v, it_result);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* To combine int a union in ascending order with the user_defined binary predicate mod_lesser */
    it_result = algo_set_union_if(vector_begin(pvec_v3a), vector_end(pvec_v3a),
        vector_begin(pvec_v3b), vector_end(pvec_v3b), vector_begin(pvec_v3),
        _mod_lesser);
    printf("Union of source ranges with binary predicate mod_lesser order\n"
           "vector v3 = ( ");
    for(it_v = vector_begin(pvec_v3);
        !iterator_equal(it_v, it_result);
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    vector_destroy(pvec_v1a);
    vector_destroy(pvec_v1b);
    vector_destroy(pvec_v1);
    vector_destroy(pvec_v2a);
    vector_destroy(pvec_v2b);
    vector_destroy(pvec_v2);
    vector_destroy(pvec_v3a);
    vector_destroy(pvec_v3b);
    vector_destroy(pvec_v3);

    return 0;
}

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ? true : false;
}
