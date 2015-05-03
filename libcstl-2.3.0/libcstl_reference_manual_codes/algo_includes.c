/*
 * algo_includes.c
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
    vector_t* pvec_v2a = create_vector(int);
    vector_t* pvec_v2b = create_vector(int);
    vector_t* pvec_v3a = create_vector(int);
    vector_t* pvec_v3b = create_vector(int);
    vector_iterator_t it_v;
    bool_t b_result;
    int i = 0;

    if(pvec_v1a == NULL || pvec_v1b == NULL ||
       pvec_v2a == NULL || pvec_v2b == NULL ||
       pvec_v3a == NULL || pvec_v3b == NULL)
    {
        return -1;
    }

    vector_init(pvec_v1a);
    vector_init(pvec_v1b);
    vector_init(pvec_v2a);
    vector_init(pvec_v2b);
    vector_init(pvec_v3a);
    vector_init(pvec_v3b);

    /* Constructing vectors v1a and v1b with default less than ordering */
    for(i = -2; i <= 4; ++i)
    {
        vector_push_back(pvec_v1a, i);
    }
    for(i = -2; i <= 3; ++i)
    {
        vector_push_back(pvec_v1b, i);
    }
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
    algo_sort_if(vector_begin(pvec_v2a), vector_end(pvec_v2a), fun_greater_int);
    algo_sort_if(vector_begin(pvec_v2b), vector_end(pvec_v2b), fun_greater_int);
    vector_pop_back(pvec_v2a);
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
    algo_reverse(vector_begin(pvec_v3a), vector_end(pvec_v3a));
    vector_pop_back(pvec_v3a);
    vector_pop_back(pvec_v3a);
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
           "binary predicate mod_lesser is v3b = ( ");
    for(it_v = vector_begin(pvec_v3b);
        !iterator_equal(it_v, vector_end(pvec_v3b));
        it_v = iterator_next(it_v))
    {
        printf("%d ", *(int*)iterator_get_pointer(it_v));
    }
    printf(")\n");

    /* 
     * To test for inclusion under an assceding order
     * with the default binary predicate less
     */
    b_result = algo_includes(vector_begin(pvec_v1a), vector_end(pvec_v1a),
        vector_begin(pvec_v1b), vector_end(pvec_v1b));
    if(b_result)
    {
        printf("All the elements in vector v1b are contained in vector v1a.\n");
    }
    else
    {
        printf("At least one of the elements in vector v1b "
               "is not contained in vector v1a.\n");
    }

    /* 
     * To test for inclusion under an assceding order
     * with the default binary predicate greater
     */
    b_result = algo_includes_if(vector_begin(pvec_v2a), vector_end(pvec_v2a),
        vector_begin(pvec_v2b), vector_end(pvec_v2b), fun_greater_int);
    if(b_result)
    {
        printf("All the elements in vector v2b are contained in vector v2a.\n");
    }
    else
    {
        printf("At least one of the elements in vector v2b "
               "is not contained in vector v2a.\n");
    }

    /* 
     * To test for inclusion under an assceding order
     * with the default binary predicate mod_lesser
     */
    b_result = algo_includes_if(vector_begin(pvec_v3a), vector_end(pvec_v3a),
        vector_begin(pvec_v3b), vector_end(pvec_v3b), _mod_lesser);
    if(b_result)
    {
        printf("All the elements in vector v3b are contained in vector v3a.\n");
    }
    else
    {
        printf("At least one of the elements in vector v3b "
               "is not contained in vector v3a.\n");
    }

    vector_destroy(pvec_v1a);
    vector_destroy(pvec_v1b);
    vector_destroy(pvec_v2a);
    vector_destroy(pvec_v2b);
    vector_destroy(pvec_v3a);
    vector_destroy(pvec_v3b);

    return 0;
}

static void _mod_lesser(const void* cpv_first, const void* cpv_second, void* pv_output)
{
    *(bool_t*)pv_output = abs(*(int*)cpv_first) < abs(*(int*)cpv_second) ? true : false;
}
